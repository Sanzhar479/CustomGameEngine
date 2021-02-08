#include "Engine/Core/CEngine.h"
#include "Game/Game1.h"
CEngine* engine;

int main(int argc, char* argv[])
{
	CEngine::GetInstance()->SetGameInterface(new Game1);
	if (!CEngine::GetInstance()->OnCreate("Game Engine", 800, 600))
	{
		Debug::FatalError("Engine Failed to Initialize", "Main.cpp", __LINE__);
	}
	CEngine::GetInstance()->Run();
	return 0;
}