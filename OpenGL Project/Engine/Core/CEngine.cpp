#include "CEngine.h"

std::unique_ptr<CEngine> CEngine::engineInstance = nullptr;

CEngine::CEngine() :window(nullptr),isRunning(false),fps(60), gameInterface(nullptr), currentSceneNum(0)
{
}

CEngine::~CEngine()
{
}

CEngine* CEngine::GetInstance()
{
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new CEngine);
		Debug::Info("Engine Instance was reseted", "CoreEngine.cpp", __LINE__);
	}
	return engineInstance.get();
}

bool CEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::OnCreate();
	window = new Window();
	if (!window->OnCreate(name_,width_,height_))
	{
		Debug::FatalError("Failed to initialize window", "CEngine.cpp", __LINE__);
		OnDestroy();
		return isRunning=false;
	}
	ShaderHandler::GetInstance()->CreateProgram("colourShader", 
		"./Shaders/ColourVertexShader.glsl",
		"./Shaders/ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("defaultShader",
		"./Shaders/VertexShader.glsl",
		"./Shaders/FragmentShader.glsl");
	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::FatalError("Game failed to initialize", "CEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}
	Debug::Info("Everything worked", "CEngine.cpp", __LINE__);
	timer.Start();
	return isRunning = true;
}

void CEngine::Run()
{
	while (isRunning)
	{
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	//if (!isRunning) 
	//{
		OnDestroy();
	//}
}

void CEngine::Exit()
{
	isRunning = false;
}

bool CEngine::GetIsRunning() const
{
	return isRunning;
}

void CEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}



int CEngine::GetCurrentScene() const {
	return currentSceneNum;
}

float CEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float CEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* CEngine::GetCamera() const
{
	return camera;
}

void CEngine::SetGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}
void CEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}
void CEngine::Render()
{
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface) 
	{
		gameInterface->Render();
	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void CEngine::Update(const float deltaTime_)
{
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();

	delete gameInterface;
	gameInterface = nullptr;

	delete camera;
	camera = nullptr;

	delete window;
	window = nullptr;

	
	SDL_Quit();
	exit(0);
}