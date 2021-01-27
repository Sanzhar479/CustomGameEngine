#include "Engine/Core/CEngine.h"
CEngine* engine;

int main(int argc, char* argv[])
{
	if (!CEngine::GetInstance()->OnCreate("Game Engine", 800, 600))
	{
		std:: cout<< "Enine Failed to Initialize" << std::endl;
	}
	CEngine::GetInstance()->Run();
	return 0;
}