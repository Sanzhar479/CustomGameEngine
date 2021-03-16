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
#include "../Graphics/TextureHandler.h"
#include "../Camera/Camera.h"
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
	bool GetIsRunning() const;
	int GetCurrentScene() const;
	float GetScreenWidth() const;
	float GetScreenHeight() const;
	Camera* GetCamera() const;

	void SetCurrentScene(int sceneNum_);
	void SetGameInterface(GameInterface* gameInterface_);
	void SetCamera(Camera* camera_);
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
	Camera* camera;
};

#endif