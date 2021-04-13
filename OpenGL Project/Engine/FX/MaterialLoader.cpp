#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}
void MaterialLoader::LoadMaterial(std::string filePath_){
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = Loadtexture(matName);
			m.name = matName;
		}
	
	}

	if (m.diffuseMap != 0) { MaterialHandler::GetInstance()->AddMaterial(m); }
	in.close();
}

GLuint MaterialLoader::Loadtexture(std::string fileName_){
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Assets/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}

	return currentTexture;
}
