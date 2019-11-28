#include "pch.h"
#include "Application.h"
#include "MeshRenderer.h"
//#include "Quad.h"
#include "Common.h"
#include "CameraComponent.h"
#include "Input.h"
Application* Application::m_application = nullptr;

Application::Application()
{
	m_Resources = Resources::GetInstance();
	m_EntityManager = EntityManager::GetInstance();
}
void Application::Init()
{
	//performing initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) //ensure intialisation is successful, if not 0 , wasnt successful so provide error feedback and close application
	{
		LOG_ERROR(SDL_GetError());
		exit(-1);
	}
	LOG_INFO("Successfull : SDL_INIT_EVERYTHING ");
	//setting openGL version to 4.2
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	//setting openGL context to core, not compatibility, Core = disable depreciated functions, compatability = enable them
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//creating window
	m_window = SDL_CreateWindow("Rocky Engine : Engine Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL);

	if (m_window == nullptr)
	{
		LOG_ERROR("NULL POINTER : m_window");
		exit(-1);
	}
	SDL_CaptureMouse(SDL_TRUE);
	LOG_DEBUG("ROCKY ENGINE: INTIALISED");

	OpenGlInit();
	GameInit();

}

void Application::OpenGlInit()
{
	//creating context (our opengl statemachine in which all our GL calls will refer to)
	m_glContext = SDL_GL_CreateContext(m_window);
	CHECK_GL_ERROR();
	SDL_GL_SetSwapInterval(1); // Set the sync of the front and back buffer swapping

   //initialsing glew (do this after establishing context!)
	GLenum err = glewInit(); // Initialise as enum to check against the GLEW_OK to determine if intialised ok , if not error output and close application
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) <<
			std::endl;
		exit(-1);
	}
	LOG_INFO("Successfull: GLEW_OK ");

	//Smooth shading
	GL_ATTEMPT(glShadeModel(GL_SMOOTH));
	//enable depth testing
	GL_ATTEMPT(glEnable(GL_DEPTH_TEST));
	//set less or equal function for depth testing
	GL_ATTEMPT(glDepthFunc(GL_LEQUAL));

	//Enable blending
	glEnable(GL_BLEND);
	GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	//turn on back face culling  TODO :  TURN BACK ON ON
	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));

	glViewport(0, 0, (GLsizei)m_windowWidth, (GLsizei)m_windowHeight); // Set up the view port , 0 ,0 specifies the lower left of the viewport in pixels and then the window width and height are prov

}
void Application::GameInit()
{
	LoadResources();
	InitialiseEntities();
}
void Application::LoadResources()
{
	//Loading resources ( Models, Textures, Shaders
	m_Resources->AddModel("Cube.obj");
	m_Resources->AddTexture("Wood.jpg");
	m_Resources->AddShader((new ShaderProgram(ASSET_PATH + "simple_VERT.glsl", ASSET_PATH + "simple_FRAG.glsl")), "GenericShader");
}
void Application::InitialiseEntities()
{
	// Creating Usable Entity with camera component

	FPSPlayer = m_EntityManager->CreateEntity("FPSPlayer");
	CameraComponent* camComp = new CameraComponent();
	FPSPlayer->AddComponent(camComp);
	camComp->Start(CameraType::FPS);

	cube = m_EntityManager->CreateEntity("CubeEntity");
	cube->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Cube.obj"), Resources::GetInstance()->GetShader("GenericShader"), Resources::GetInstance()->GetTexture("Wood.jpg")));
	cube->GetTransform()->SetPosition(glm::vec3((0.0f, 0.0f, -10.0f)));
	cube->GetTransform()->SetScale(glm::vec3(5.0f, 5.0f, 5.f));

}
void Application::Loop()
{
	m_appState = ApplicationState::RUNNING;

	auto previousTicks= std::chrono::high_resolution_clock::now();
	SDL_Event event;

	while(m_appState != ApplicationState::QUITING)
	{
		//poll SDL events

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				m_appState = ApplicationState::QUITING;
				break;

			case SDL_WINDOWEVENT_CLOSE:
				m_appState = ApplicationState::QUITING;
				break;

			case SDL_KEYDOWN:
				INPUT->SetKey(event.key.keysym.sym, true);
				//LOG_DEBUG(std::to_string(event.key.keysym.sym) + "  DOWN");
				if (INPUT->GetKey(SDLK_f))
				{
					m_EntityManager->DisplayAllEntities();
				}
				if (INPUT->GetKey(SDLK_k))
				{
					m_EntityManager->Destroy(cube3,deltaTime,3.0f);
				}
				if (INPUT->GetKey(SDLK_j))
				{
					m_EntityManager->ReleaseEntities();
				}

				break;
			case SDL_KEYUP:
				INPUT->SetKey(event.key.keysym.sym, false);
				//LOG_DEBUG(std::to_string(event.key.keysym.sym) + "  UP");
		
				break;
			case SDL_MOUSEMOTION:
				INPUT->MoveMouse(glm::ivec2(event.motion.xrel, event.motion.yrel));
				break;
			}
		}

		m_EntityManager->MovableEntity(FPSPlayer, deltaTime, 2.f);


		auto currentTicks = std::chrono::high_resolution_clock::now();
		deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - previousTicks).count() / 100000;
		m_worldDeltaTime = deltaTime;
		previousTicks = currentTicks;

		Update(deltaTime);
		Render();
		SwapBuffer();
	}
}
void Application::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}
void Application::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_mainCamera->Recalculate();
	
	for (auto itr = m_EntityManager->m_entities.begin(); itr != m_EntityManager->m_entities.end(); itr++)
	{
		itr->second->OnRender();
	}
}
void Application::SetCamera(Camera* camera)
{
	if (camera != nullptr)
	{
		m_mainCamera = camera;
	}
}
void Application::Update(float deltaTime)
{
	for (auto itr = m_EntityManager->m_entities.begin(); itr != m_EntityManager->m_entities.end(); itr++)
	{
		itr->second->OnUpdate(deltaTime);
	}
}
void Application::Quit()
{
	//Close SDL
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}

Application::~Application()
{

}

Application* Application::Instance()
{
	if (m_application == nullptr)
	{
		m_application = new Application();
	}

	return m_application;
}

void Application::Run()
{
	Init();
	Loop();
	Quit();
}