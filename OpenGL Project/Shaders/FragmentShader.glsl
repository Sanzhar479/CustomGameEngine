#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

uniform sampler2D inputTexture;
uniform vec3 camPos;

out vec4 fColour;
struct Light
{
vec3 position;
vec3 lightColour;
float ambience;
float diff;
float spec;
};

uniform Light light;

void main()
{
fColour = texture(inputTexture,TexCoords);

vec3 ambience = light.ambience* texture(inputTexture,TexCoords).rgb* light.lightColour;

vec3 norm = normalize(Normal);
vec3 lightDir= normalize(light.position-FragPosition);
float diff= max(dot(norm,lightDir),0.0);
vec3 diffuse= (diff*light.diff)* texture(inputTexture, TexCoords).rgb
* light.lightColour;

vec3 viewDir= normalize(camPos - FragPosition);
vec3 reflectDir= reflect(-lightDir,norm);
float spec= pow(max(dot(viewDir,reflectDir),0.0),32);
vec3 specular= (spec * light.spec)* light.lightColour;

vec3 result= ambience + diffuse + specular;
fColour = vec4(result,1.0f);
}