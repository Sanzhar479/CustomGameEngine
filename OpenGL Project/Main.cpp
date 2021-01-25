#include "Engine/Core/CEngine.h"
CEngine* engine;

int main(int argc, char* argv[])
{
	engine = new CEngine();
	if (!engine->OnCreate("Game Engine", 800, 600))
	{
		delete engine;
		engine = nullptr;
		return 0;
	}
	engine->Run();
	delete engine;
	engine = nullptr;
	return 0;
}