#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <vector>
#include <glm/glm.hpp>
#include <glew.h>
#include <memory>
#include <string>

struct Material 
{
	inline Material() :diffuseMap(0), shininess(32.0f), transparency(1.0f),
		ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f)),
			name("") {}

	GLuint diffuseMap;//newmtl

	float shininess;//NS
	float transparency;//d

	glm::vec3 ambient;//ka
	glm::vec3 diffuse;//kd
	glm::vec3 specular;//ks
	std::string name;
};


class MaterialHandler
{
public:
	MaterialHandler(const MaterialHandler&) = delete;
	MaterialHandler(MaterialHandler&&) = delete;
	MaterialHandler& operator=(const MaterialHandler&) = delete;
	MaterialHandler& operator =(MaterialHandler&&) = delete;

	static MaterialHandler* GetInstance();
	void AddMaterial(Material mat_);
	const Material GetMaterial(const std::string& matName_);
	void OnDestroy();

private:
	MaterialHandler();
	~MaterialHandler();

	static std::unique_ptr<MaterialHandler> materialInstance;
	friend std::default_delete<MaterialHandler>;

		static std::vector<Material> materials;
};

#endif