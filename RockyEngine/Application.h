#pragma once
#include "pch.h"
enum ApplicationState
{
	INITILISING,RUNNING,QUITING
};
class Application
{
private:

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

public:

	~Application();
	static Application* Instance();
	void Run();

};

