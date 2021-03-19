#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

uniform sampler2D inputTexture;
uniform vec3 camPos;
uniform Light light;

out vec4 fColour;

struct Light
{
glm::vec3 position;
glm::vec3 lightColour;
float ambience = 0.0f;
float diff = 0.0f;
float spec = 0.0f;
} 

void main()
{
fColour = texture(inputTexture,TexCoords);

vec3 ambience = light.ambience* texture(inputTexture,TexCoords).rgb* light.lightColour;

vec3 norm = normalize(Normal);
vec3 lightDir= normalize(light.position-FragPosition);
float diff= max(dot(norm,lightDir),0.0);
vec3 diffuse= (diff*light.diffuse)* texture(inputTexture, TexCoords).rgb
* light.lightColour;

vec3 viewDir= normalize(viewPosition-FragPosition);
vec3 reflectDir= reflect(-lightDir,norm);
float spec= pow(max(dot(viewDir,reflectDir),0.0),32);
vec3 specular= (spec * light.specular)* light.lightColour;

vec3 result= ambience + diffuse + specular;
fColour = vec4(result,1.0f);
}