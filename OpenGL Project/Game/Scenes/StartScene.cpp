#include "StartScene.h"
StartScene::StartScene() {

}
StartScene::~StartScene() {

}
bool StartScene::OnCreate() {
	Debug::Info("Start Scene", "StartScene.cpp", __LINE__);
	CEngine::GetInstance()->SetCurrentScene(1);
	return true;
}
void StartScene::Update(const float deltaTime_) {

}
void StartScene::Render() {

}