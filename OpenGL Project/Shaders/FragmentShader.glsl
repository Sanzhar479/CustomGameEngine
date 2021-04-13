#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

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

struct Material 
{
	sampler2D diffuseMap;//newmtl

	float shininess;//NS
	float transparency;//d

	vec3 ambient;//ka
	vec3 diffuse;//kd
	vec3 specular;//ks
    string name;
};

uniform Material material;
uniform Light light;

void main()
{

//AMBIENT
vec3 ambience = light.ambience * material.ambient *texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

//DIFFUSE
vec3 norm = normalize(Normal);
vec3 lightDir= normalize(light.position-FragPosition);
float diff= max(dot(norm,lightDir),0.0);
vec3 diffuse= (diff * material.diffuse)* texture(material.diffuseMap, TexCoords).rgb
* light.lightColour;

//SPECIALR
vec3 viewDir= normalize(camPos - FragPosition);
vec3 reflectDir= reflect(-lightDir,norm);
float spec= pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
vec3 specular= (spec * material.specular)* light.lightColour;

vec3 result= ambient + diffuse + specular;


fColour = vec4(result, material.transparency);
}