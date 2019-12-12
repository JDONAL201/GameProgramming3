#pragma once
#include "Entity.h"
#include "Resources.h"
#include "EntityManager.h"

//#include "SkyBox.h"
#define WINDOW_W Application::Instance()->GetWindowWidth();
#define WINDOW_H Application::Instance()->GetWindowHeight();

class Camera; // forward declare

enum ApplicationState
{
	INITILISING,RUNNING,QUITING
};
class Application
{
	
private:
	Application();
	float deltaTime = 0.0f;
	int m_windowWidth = 1280;
	int m_windowHeight = 720;
	float m_worldDeltaTime = 0.f;

	
	void Init();
	void OpenGlInit();
	void Loop();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void SwapBuffer();
	void InitialiseEntities();
	void LoadResources();
	void ShadowPass();
	void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 viewPos);

	ApplicationState m_appState = ApplicationState::INITILISING;
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;
	Camera* m_mainCamera = nullptr;
	static Application* m_application;
	EntityManager* m_EntityManager;
	Resources* m_Resources;

	std::vector<std::string> enviro_map_faces;
	bool ShadowPassState = false;


	GLuint u_ambientIntensity = 0, u_ambientColor = 0, u_direction = 0, u_diffIntensity = 0, u_viewPosition = 0, u_model = 0, u_projection = 0, u_view = 0 , u_specular = 0, u_shine = 0;


public:

	~Application();
	static Application* Instance();
	void Run();
	void GameInit();
	inline int GetWindowHeight() { return m_windowHeight; }
	inline int GetWindowWidth() { return m_windowWidth; }
	bool GetShadowPass() { return ShadowPassState; }

	inline Camera* GetCamera() { return m_mainCamera; }
	void SetCamera(Camera* camera);

};
