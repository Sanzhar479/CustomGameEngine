#include "LoadOBJModel.h"

LoadObjModel::LoadObjModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()),
textureCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()),
normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material()) {
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}
LoadObjModel::~LoadObjModel() {
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}
void LoadObjModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_) {
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}
std::vector<SubMesh> LoadObjModel::GetSubMeshes() {
	return subMeshes;
}
void LoadObjModel::LoadModel(const std::string& filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_,
			"LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		//vertex data
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "vn") {
			std::stringstream vn(line.substr(2));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "vt") {
			std::stringstream vt(line.substr(2));
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}
		else if (line.substr(0, 2) == "f ") {
			std::stringstream f(line.substr(2));
			unsigned int f1[3], f2[3], f3[3];
			char u;
			f >> f1[0] >> u >> f2[0] >> u >> f3[0] >> f1[1] >> u >> f2[1] >> u >> f3[1] >> f1[2] >> u >> f2[2] >> u >> f3[2];
			for (int i = 0; i < 3; i++) {
				indices.push_back(f1[i]);
				textureIndices.push_back(f2[i]);
				normalIndices.push_back(f3[i]);
			}
		}
		//new mesh
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0)
				PostProcessing();
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadObjModel::PostProcessing() {
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;

		vert.position = vertices[indices[i]-1];
		vert.normal = normals[normalIndices[i]-1];
		vert.textureCoordinates = textureCoords[textureIndices[i]-1];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;
	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}
void LoadObjModel::LoadMaterial(const std::string& matName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}
void LoadObjModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	
	MaterialLoader::LoadMaterial(matFilePath_);
	
	
	/*std::ifstream in(matFilePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl") {
			LoadMaterial(line.substr(7));
		}
	}*/
}