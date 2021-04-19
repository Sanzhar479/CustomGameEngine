#include "MaterialHandler.h"

std::unique_ptr<MaterialHandler> MaterialHandler::materialInstance = nullptr;
std::vector<Material> MaterialHandler::materials=
std::vector<Material>();

MaterialHandler::MaterialHandler()
{
	materials.reserve(30);
}

MaterialHandler::~MaterialHandler()
{
	OnDestroy();
}



MaterialHandler* MaterialHandler::GetInstance()
{
	if (materialInstance.get() == nullptr) {
		materialInstance.reset(new MaterialHandler);
	}
	return materialInstance.get();
}

void MaterialHandler::AddMaterial(Material mat_)
{
	materials.push_back(mat_);
}

const Material MaterialHandler::GetMaterial(const std::string& matName_)
{
	for (size_t i = 0; i < materials.size(); i++)
	{
		if (materials[i].name == matName_)
			return materials[i];
	}
	return Material();
}

void MaterialHandler::OnDestroy()
{
	if (materials.size() > 0) { materials.clear(); }
}

