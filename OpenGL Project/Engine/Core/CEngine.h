#ifndef CENGINE_H
#define CENGINE_H
#include "Window.h"
#include <memory>
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
class CEngine
{public:
	CEngine(const CEngine&) = delete;
	CEngine(CEngine&&) = delete;
	CEngine& operator=(const CEngine&) = delete;
	CEngine& operator=(CEngine&&) = delete;

	static CEngine* GetInstance();
	CEngine();
	~CEngine();
	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();
	bool GetIsRunning();
	int GetCurrentScene() const;
	void SetCurrentScene(int sceneNum_);
	void SetGameInterface(GameInterface* gameInterface_);
private:
	
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render();

	static std::unique_ptr<CEngine> engineInstance;
	friend std::default_delete<CEngine>;

	Window* window;
	bool isRunning;
	Timer timer;
	unsigned int fps;
	GameInterface* gameInterface;
	int currentSceneNum;
};

#endif