#include "GameScene.h"
GameScene::GameScene(): shape(nullptr)
{
	/*for (size_t i = 0; i < sizeof(shape) / sizeof(shape[0]); i++)
		shape[i] = nullptr;*/
}
GameScene::~GameScene() {
	/*for (size_t i = 0; i < sizeof(shape) / sizeof(shape[0]); i++) {
		delete shape[i];
		shape[i] = nullptr;
	}*/
	delete shape;
	shape = nullptr;
}
bool GameScene::OnCreate() {
	Debug::Info("We switched to the game scene", "GameScene.cpp", __LINE__);
	/*Vertex* v2 = new Vertex();
	std::vector<Vertex*> vertexList2[3];
	Vertex v;
	std::vector<Vertex> vertexList[3];
	for (size_t i = 0; i < sizeof(vertexList) / sizeof(vertexList[0]); i++)
	{
		vertexList2[i].reserve(3);
		vertexList[i].reserve(3);
	}*/

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(3);
	v.position = glm::vec3(0.0f, 0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.colour = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);
	

	/*for (size_t i = 0; i < sizeof(vertexList) / sizeof(vertexList[0]); i++)
	{*/
		Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"));
		model->AddMesh(new Mesh(vertexList));
		shape = new GameObject(model);
	
		return true;
}
void GameScene::Update(const float deltaTime_) {

}
void GameScene::Render() {
	
		shape->Render();
}