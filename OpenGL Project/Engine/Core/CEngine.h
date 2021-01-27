#ifndef CENGINE_H
#define CENGINE_H
#include "Window.h"
#include <memory>
class CEngine
{public:
	CEngine(const CEngine&) = delete;
	CEngine(CEngine&&) = delete;
	CEngine& operator=(const CEngine&) = delete;
	CEngine& operator=(CEngine&&) = delete;

	static CEngine* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();

private:
	CEngine();
	~CEngine();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render();

	static std::unique_ptr<CEngine> engineInstance;
	friend std::default_delete<CEngine>;

	Window* window;
	bool isRunning;
};

#endif