#include "pch.h"
#include "Application.h"
#include "MeshRenderer.h"
//#include "Quad.h"
#include "Common.h"
#include "CameraComponent.h"
#include "Input.h"
#include "Physics.h"
#include "BoxShape.h"
#include "SphereShape.h"
#include "RigidBody.h"
#include "CapsuleShape.h"
#include "ConeShape.h"
#include "CylinderShape.h"
#include "ControllerComponent.h";


CameraComponent* camComp;
ControllerComponent* controller; //TODO GET RID OF THESE AT THE TOP 
const unsigned int shadowWidth = 1024; //TODO CHANGE HOW GETS HEIGHT N WIDTH ?
const unsigned int	shadowHeight = 1024;

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
		LOG_ERROR("Window is nullptr");
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

	//Enable blending //todo: come back to this , this is causing transparency 
	//glEnable(GL_BLEND);
	//GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));

	glViewport(0, 0, (GLsizei)m_windowWidth, (GLsizei)m_windowHeight); // Set up the view port , 0 ,0 specifies the lower left of the viewport in pixels and then the window width and height are prov

	SDL_SetRelativeMouseMode(SDL_TRUE);
}
void Application::GameInit()
{
	LoadResources();
	InitialiseEntities();

	unsigned int m_fbo;
	//TODO REMOVE THIS FROM HERE 
	GL_ATTEMPT(glGenFramebuffers(1, &m_fbo));
	//const unsigned int shadowWidth = 1024; //TODO CHANGE HOW GETS HEIGHT N WIDTH ?
	//const unsigned int	shadowHeight = 1024;

	unsigned int shadowMap;
	GL_ATTEMPT(glGenTextures(1, &shadowMap));
	GL_ATTEMPT(glBindTexture(GL_TEXTURE_2D, shadowMap));
	GL_ATTEMPT(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GL_ATTEMPT(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
	GL_ATTEMPT(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0));

	GL_ATTEMPT(glDrawBuffer(GL_NONE));
	GL_ATTEMPT(glReadBuffer(GL_NONE));//telling opengl that we are not using the color buffer

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
void Application::LoadResources()
{
	//Loading resources ( Models, Textures, Shaders
	//m_Resources->AddModel("error.obj", "");
	//m_Resources->AddModelWithMat("Robot and Plant.obj", "Clank//");
	//m_Resources->AddModel("batman.obj", "folder//");
	//m_Resources->AddModel("CHALLENGER71.obj", "folder3//");
	m_Resources->AddModel("Cube.obj");
	m_Resources->AddModelWithMat("Joker.obj" , "folder2//");
	m_Resources->AddTexture("missing.png");
	m_Resources->AddTexture("lava.png");
	m_Resources->AddShader((new ShaderProgram(SHADER_PATH + "simple_VERT.glsl", SHADER_PATH + "simple_FRAG.glsl")), "GenericShader");
	
}
void Application::ShadowPass()
{
	//////TODO: The rendering of the framebuffer 
	////glViewport(0, 0, shadowWidth, shadowHeight);
	////glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	////glClear(GL_DEPTH_BUFFER_BIT);
	////

}
void Application::InitialiseEntities()
{
	// Creating Usable Entity with camera component
	Entity* SceneEntity = m_EntityManager->CreateEntity("SceneEntity");
	SceneEntity->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 0.f));
	SceneEntity->AddComponent(new CameraComponent());
	SceneEntity->AddComponent(new ControllerComponent());
	controller = SceneEntity->GetComponent<ControllerComponent>();

	Entity* cube = m_EntityManager->CreateEntity("CubeEntity");
	cube->AddComponent(new MeshRenderer(m_Resources->GetModel("Cube.obj"), m_Resources->GetShader("GenericShader"))); //IF NO TEXTURE OR MATERIAL , DEFAULT WILL BE APPLIED
	cube->GetTransform()->SetPosition(glm::vec3(0.0f, -10.0f, 20.0f));
	cube->AddComponent<RigidBody>();
	cube->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)));
	cube->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	cube->GetTransform()->SetScale(glm::vec3(100.f, 1.f, 100.f));

	Entity* Sphere = m_EntityManager->CreateEntity("Cube");
	Sphere->AddComponent(new MeshRenderer(m_Resources->GetModel("Cube.obj"), m_Resources->GetShader("GenericShader"),m_Resources->GetTexture("lava.png"))); 
	Sphere->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, -20.0f));
	//Sphere->AddComponent<RigidBody>();
	//Sphere->GetComponent<RigidBody>()->Init(new SphereShape(5.f));
	Sphere->GetTransform()->SetScale(glm::vec3(10.f, 10.f, 10.f));


	//Entity* Clank = m_EntityManager->CreateEntity("Robot");
	//Clank->AddComponent(new MeshRenderer(m_Resources->GetModel("Robot and Plant.obj"), m_Resources->GetShader("GenericShader")));
	//Clank->AddComponent<RigidBody>();
	//Clank->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)));
	//Clank->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	//Clank->GetTransform()->SetPosition(glm::vec3((0.0f, 0.0f, 0.0f)));
	//Clank->GetTransform()->SetRotation(glm::quat(0.f, 0.f, 180.f, 0.f));
	//Clank->GetTransform()->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));

	//Entity* BatmanBuilding = m_EntityManager->CreateEntity("BatBuilding");
	//BatmanBuilding->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("batman.obj"), Resources::GetInstance()->GetShader("GenericShader")));
	//BatmanBuilding->GetTransform()->SetPosition(glm::vec3(80.0f, 0.0f, 0.f));
	//BatmanBuilding->GetTransform()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	//
	//Entity* Joker = m_EntityManager->CreateEntity("Joker");
	//Joker->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Joker.obj"), Resources::GetInstance()->GetShader("GenericShader") , m_Resources->GetTexture("lava.png")));
	//Joker->GetTransform()->SetPosition(glm::vec3(-50.0f, 0.0f, -50.f));
	//Joker->GetTransform()->SetRotation(glm::quat(270.f, 0.f, 0.f, 0.f));
	//Joker->GetTransform()->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	//Joker->AddComponent<RigidBody>();
	//Joker->GetComponent<RigidBody>()->Init(new BoxShape(Joker->GetTransform()->GetScale()));

	for (int i = 0; i < 100; i++)
	{
		Entity* a = m_EntityManager->CreateEntity("cube" + std::to_string(i));
		a->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Cube.obj"), Resources::GetInstance()->GetShader("GenericShader"), m_Resources->GetTexture("lava.png")));
		a->GetTransform()->SetPosition(glm::vec3(-40, 5.f * i, 40.f));
		a->GetTransform()->SetScale(glm::vec3(5, 5, 5));
		a->AddComponent<RigidBody>();
		a->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(5.f, 5.f, 5.f)));
	}
	
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
					//m_EntityManager->Destroy(Clank,deltaTime,3.0f);
				}
				if (INPUT->GetKey(SDLK_UP))
				{
					//Clank->GetComponent<RigidBody>()->AddForce(glm::vec3(0,0,-1), Clank->GetTransform()->GetPosition(),10.f);
				}
				if (INPUT->GetKey(SDLK_RIGHT))
				{
					std::cout << "HELLO" << std::endl;
					//Clank->GetComponent<RigidBody>()->AddTorque(Clank->GetTransform()->GetRight(), 100.f);
				}
				if (INPUT->GetKey(SDLK_j))
				{
					m_EntityManager->ReleaseEntities();
				}

				if (INPUT->GetKey(SDLK_ESCAPE))
				{
					m_appState = ApplicationState::QUITING;
				}

				break;
			case SDL_KEYUP:
				INPUT->SetKey(event.key.keysym.sym, false);
				//LOG_DEBUG(std::to_string(event.key.keysym.sym) + "  UP");
		
				break;
			case SDL_MOUSEMOTION:
				INPUT->MoveMouse(glm::ivec2(event.motion.xrel, event.motion.yrel));
				m_EntityManager->GetEntity("SceneEntity")->GetComponent<ControllerComponent>()->SetMouseMotion();
			/*	if (InitPos) 
				{
					lastX = event.motion.xrel;
					lastY = event.motion.yrel;
				}
				float x = event.motion.xrel - lastX;
				float y = event.motion.yrel - lastY;
				controller->SetMouseMotion(x, y);*/
				//m_EntityManager->Rotate(SceneEntity, changeInX, changeInY);
				break;
			}

		}
		auto currentTicks = std::chrono::high_resolution_clock::now();
		deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - previousTicks).count() / 100000;
		m_worldDeltaTime = deltaTime;
		previousTicks = currentTicks;

		Physics::GetInstance()->Update(deltaTime);
		
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

	//m_EntityManager->GetEntity("Cube")->OnRender();

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
	Physics::GetInstance()->Quit();
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