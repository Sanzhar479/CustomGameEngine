#include "Game1.h"
Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr) {

}
Game1::~Game1() {
	delete currentScene;
	currentScene = nullptr;
}
bool Game1::OnCreate() {
	if (CEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();;
	}

	std::cout << "Engine's scene is not initialiized to 0" << std::endl;
	return false;
}
void Game1::Update(const float deltaTime_) {
	if (currentSceneNum != CEngine::GetInstance()->GetCurrentScene())
		BuildScene();
	currentScene->Update(deltaTime_);
}
void Game1::Render() {
	currentScene->Render();
}
void Game1::BuildScene() {
	delete currentScene;
	currentScene = nullptr;
	switch (CEngine::GetInstance()->GetCurrentScene()) {
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}
	currentSceneNum = CEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		std::cout << "Scene failed to be created" << std::endl;
		CEngine::GetInstance()->Exit();
	}
}