#include "GameScene.h"
GameScene::GameScene()
{
	for (size_t i = 0; i < sizeof(shape) / sizeof(shape[0]); i++)
		shape[i] = nullptr;
}
GameScene::~GameScene() {
	for (size_t i = 0; i < sizeof(shape) / sizeof(shape[0]); i++) {
		delete shape[i];
		shape[i] = nullptr;
	}
}
bool GameScene::OnCreate() {
	Debug::Info("We switched to the game scene", "GameScene.cpp", __LINE__);
	Vertex* v2 = new Vertex();
	std::vector<Vertex*> vertexList2[3];
	Vertex v;
	std::vector<Vertex> vertexList[3];
	for (size_t i = 0; i < sizeof(vertexList) / sizeof(vertexList[0]); i++)
	{
		vertexList2[i].reserve(3);
		vertexList[i].reserve(3);
	}
	v2->position = glm::vec3(-0.25f, 0.0f, 0.0f);
	vertexList2[0].push_back(v2);
	v2->position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList2[0].push_back(v2);
	v2->position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertexList2[0].push_back(v2);

	v.position = glm::vec3(-0.25f, 0.0f, 0.0f);
	vertexList[0].push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList[0].push_back(v);
	v.position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertexList[0].push_back(v);

	v2->position = glm::vec3(0.25f, 0.0f, 0.0f);
	vertexList2[1].push_back(v2);
	v2->position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList2[1].push_back(v2);
	v2->position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertexList2[1].push_back(v2);

	v.position = glm::vec3(0.25f, 0.0f, 0.0f);
	vertexList[1].push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList[1].push_back(v);
	v.position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertexList[1].push_back(v);

	v2->position = glm::vec3(0.25f, 0.0f, 0.0f);
	vertexList2[2].push_back(v2);
	v2->position = glm::vec3(-0.25f, 0.0f, 0.0f);
	vertexList2[2].push_back(v2);
	v2->position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertexList2[2].push_back(v2);

	v.position = glm::vec3(0.25f, 0.0f, 0.0f);
	vertexList[2].push_back(v);
	v.position = glm::vec3(-0.25f, 0.0f, 0.0f);
	vertexList[2].push_back(v);
	v.position = glm::vec3(0.0f, 0.5f, 0.0f);
	vertexList[2].push_back(v);

	for (size_t i = 0; i < sizeof(vertexList) / sizeof(vertexList[0]); i++)
	{
		Model* model = new Model();
		model->AddMesh(new Mesh(vertexList[i]));
		shape[i] = new GameObject(model);
	}
	return true;
}
void GameScene::Update(const float deltaTime_) {

}
void GameScene::Render() {
	for (size_t i = 0; i < sizeof(shape) / sizeof(shape[0]); i++)
		shape[i]->Render();
}