#pragma once
#include "pch.h"
#include "Entity.h"
#define WINDOW_W Application::GetInstance()->GetWindowWidth()
#define WINDOW_H Application::GetInstance()->GetWindowHeight()

class Camera; // forward declare

enum ApplicationState
{
	INITILISING,RUNNING,QUITING
};
class Application
{
	
private:
	std::vector <Entity*> m_entities;
	Camera* m_mainCamera = nullptr;

	static Application* m_application; 
	SDL_Window* m_window = nullptr; 
	SDL_GLContext m_glContext = nullptr; 
	int m_windowWidth = 1280;
	int m_windowHeight = 720;
	ApplicationState m_appState = ApplicationState::INITILISING;
	float m_worldDeltaTime = 0.f;

	Application();
	void Init();
	void OpenGlInit();
	void Loop();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void SwapBuffer();
public:

	~Application();
	static Application* Instance();
	void Run();
	void GameInit();
	inline int GetWindowHeight() { return m_windowHeight; }
	inline int GetWindowWidth() { return m_windowWidth; }

	inline Camera* GetCamera() { return m_mainCamera; }
	void SetCamera(Camera* camera);

};

