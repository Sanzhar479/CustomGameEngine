#ifndef CENGINE_H
#define CENGINE_H
#include "Window.h"

class CEngine
{public:
	CEngine();
	~CEngine();
	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
private:
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render();

	Window* window;
	bool isRunning;
};

#endif