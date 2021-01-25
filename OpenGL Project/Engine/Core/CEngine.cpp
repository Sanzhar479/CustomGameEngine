#include "CEngine.h"

CEngine::CEngine() :window(nullptr),isRunning(false)
{
}

CEngine::~CEngine()
{
}

bool CEngine::OnCreate(std::string name_, int width_, int height_)
{
	window = new Window();
	if (!window->OnCreate(name_,width_,height_))
	{
		std::cout << "Failed to initialize window" << std::endl;
		OnDestroy();
		return isRunning=false;
	}
	return isRunning = true;
}

void CEngine::Run()
{
	while (isRunning)
	{
		Update(0.016f);
		Render();
	}
	//if (!isRunning) 
	//{
		OnDestroy();
	//}
}

bool CEngine::GetIsRunning()
{
	return isRunning;
}

void CEngine::OnDestroy()
{
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}

void CEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window->GetWindow());
}

void CEngine::Update(const float deltaTime_)
{
}