#include "pch.h"
#include "Application.h"
#include "MeshRenderer.h"
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
#include "MousePicking.h"
#include "DirectionalLight.h"

float fireRate = 0;
Entity* rollerBall = nullptr;
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
	SDL_SetRelativeMouseMode(SDL_TRUE);
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

	////Enable blending //todo: come back to this , this is causing transparency 
	//glEnable(GL_BLEND);
	//GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));


	glViewport(0, 0, (GLsizei)m_windowWidth, (GLsizei)m_windowHeight); // Set up the view port , 0 ,0 specifies the lower left of the viewport in pixels and then the window width and height are prov
}
void Application::GameInit()
{
	INPUT->InitGamePads();
	LoadResources();
	InitialiseEntities();
	projection = Application::Instance()->GetCamera()->GetProj();

}
void Application::LoadResources()
{

	LOG_DEBUG("This is a debug log");
	LOG_INFO("This is a info log");
	LOG_ERROR("This is an error log!!!");
	LOG_WARNING("This is a warning log!");
	LOG_RESOURCE("Resource notification!");

	//Loading resources ( Models, Textures, ShadersKyloRenCommandShuttle.obj
	//m_Resources->AddModelWithMat("PoliceCar.obj", "police//");
	m_Resources->AddModelWithMat("Freigther_BI_Export.obj", "space//"); 
	m_Resources->AddModelWithMat("muro.obj", "man//");
	m_Resources->AddModelWithMat("Joker.obj", "joker//");
	m_Resources->AddModelWithMat("mustang_GT.obj", "mustang//"); 
	m_Resources->AddModelWithMat("maya.obj", "maya//");
	//m_Resources->AddModelWithMat("Portal Gun.obj", "gun//");

	m_Resources->AddModel("error.obj");
	m_Resources->AddModel("Cube.obj");
	m_Resources->AddModel("sphere.obj");


	m_Resources->AddTexture("missing.png");
	m_Resources->AddTexture("lava.png");
	m_Resources->AddTexture("floor.jpg");

	m_Resources->AddShader("shadow","shadow_VERT.glsl", "shadow_FRAG.glsl");
	m_Resources->AddShader("Skybox","skybox_VERT.glsl", "skybox_FRAG.glsl");
	m_Resources->AddShader("BlinnPhong","simple_VERT.glsl", "simple_FRAG.glsl");
	

	enviro_map_faces.push_back(TEXTURE_PATH + "cubemaps//default//front.tga");
	enviro_map_faces.push_back(TEXTURE_PATH + "cubemaps//default//back.tga");
	enviro_map_faces.push_back(TEXTURE_PATH + "cubemaps//default//up.tga");
	enviro_map_faces.push_back(TEXTURE_PATH + "cubemaps//default//down.tga");
	enviro_map_faces.push_back(TEXTURE_PATH + "cubemaps//default//right.tga");
	enviro_map_faces.push_back(TEXTURE_PATH + "cubemaps//default//left.tga");
	skybox = SkyBox(enviro_map_faces);
	BlinnPhongShader = m_Resources->GetShader("BlinnPhong");
	ShadowShader = m_Resources->GetShader("shadow");

	main_LightSource = new DirectionalLight(4096, 4096,glm::vec3(1.0f, 1.0f, 1.0f), 0.15f, 0.4f, glm::vec3(-15.0f, -14.0f, 0.0f),0.01f,2); //32 multiple of 2
}
void Application::Loop()
{
	m_appState = ApplicationState::RUNNING;

	auto previousTicks= std::chrono::high_resolution_clock::now();

	while(m_appState != ApplicationState::QUITING)
	{
		//poll SDL events
		ProcessInput();
		
		auto currentTicks = std::chrono::high_resolution_clock::now();
		deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - previousTicks).count() / 100000;
		m_worldDeltaTime = deltaTime;
		previousTicks = currentTicks;

		Physics::GetInstance()->Update(deltaTime);
		Update(deltaTime);

		glm::mat4 view = Application::Instance()->GetCamera()->GetView();
		glm::vec3 viewPosition = Application::Instance()->GetCamera()->GetParentTransform()->GetPosition();
		
		m_mainCamera->Recalculate();

		ShadowPass();
		RenderPass(projection, view, viewPosition);
			
		glUseProgram(0);
		SwapBuffer();
	}
}
void Application::SwapBuffer()
{
	SDL_GL_SwapWindow(m_window);
}
void Application::ShadowPass()
{
	m_renderType = RenderType::SHADOWPASS;
	ShadowShader->Use();
	glViewport(0, 0, main_LightSource->GetShadowMap()->GetShadowWidth(), main_LightSource->GetShadowMap()->GetShadowHeight());
	main_LightSource->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	ShadowShader->SetUniformMat4("lightSpaceTransform", main_LightSource->CalculateLightTransform());
	
	Render();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Application::RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix,glm::vec3 viewPos)
{
	m_renderType = RenderType::RENDERPASS;
	glViewport(0, 0, m_windowWidth, m_windowHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	skybox.RenderSkyBox(Resources::GetInstance()->GetShader("Skybox"));
	BlinnPhongShader->Use();
	BlinnPhongShader->SetUniformMat4("proj", projectionMatrix);
	BlinnPhongShader->SetUniformMat4("view", viewMatrix);
	BlinnPhongShader->SetUniformVec3("viewPosition", glm::vec3(viewPos.x, viewPos.y, viewPos.z));
	BlinnPhongShader->SetDirectionalLight(main_LightSource);
	BlinnPhongShader->SetUniformMat4("lightSpaceTransform", main_LightSource->CalculateLightTransform());
	main_LightSource->GetShadowMap()->Read(GL_TEXTURE1);
	BlinnPhongShader->SetUniformInt("m_texture", 0);
	BlinnPhongShader->SetUniformInt("m_shadowMap", 1);
	
	
	Render();
}
void Application::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		
		if (INPUT->GamePadIsActive())
		{
			INPUT->UpdateGamePads(event);
		}

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
			if (INPUT->GetKey(SDLK_f))
			{
				if (fireRate <= 0)
				{
					glm::vec3 Point_Forward = m_EntityManager->GetEntity("Gun")->GetTransform()->GetForward();
					std::shared_ptr<Entity> projectile = m_EntityManager->CreateEntity("Projectile");
					projectile->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("sphere.obj"), Resources::GetInstance()->GetShader("BlinnPhong"), m_Resources->GetTexture("lava.png")));
					projectile->GetTransform()->SetPosition(m_EntityManager->GetEntity("SceneEntity")->GetTransform()->GetPosition());
					projectile->GetTransform()->SetScale(glm::vec3(1, 1, 1));
					projectile->AddComponent<RigidBody>();
					projectile->GetComponent<RigidBody>()->Init(new SphereShape(0.5f));
					projectile->GetComponent<RigidBody>()->AddForce(Point_Forward, projectile->GetTransform()->GetPosition(), 800.f);
					projectile->GetComponent<RigidBody>()->m_rigidbody->setRestitution(10.f);
					//m_EntityManager->DisplayAllEntities();
					fireRate = 2.f;
				}
				else
				{
					std::cout << "CANT SHOOT YET" << std::endl;
				}
			}
			if (INPUT->GetKey(SDLK_LEFT))
			{
				m_EntityManager->DisplayAllEntities();
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->m_rigidbody->clearForces();
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->AddTorque(glm::vec3(-1, 0, 0), 125.f);
			}
			if (INPUT->GetKey(SDLK_RIGHT))
			{
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->m_rigidbody->clearForces();
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->AddTorque(glm::vec3(1, 0, 0), 125.f);

			}
			if (INPUT->GetKey(SDLK_UP))
			{
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->m_rigidbody->clearForces();
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->AddForce(glm::vec3(0, 0, -1), m_EntityManager->GetEntity("PhysicsCube")->GetTransform()->GetPosition(), 35.f);

			}
			if (INPUT->GetKey(SDLK_DOWN))
			{
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->m_rigidbody->clearForces();
				m_EntityManager->GetEntity("PhysicsCube")->GetComponent<RigidBody>()->AddForce(glm::vec3(0, 0, 1), m_EntityManager->GetEntity("PhysicsCube")->GetTransform()->GetPosition(), 35.f);

			}
			if (INPUT->GetKey(SDLK_ESCAPE))
			{
				m_appState = ApplicationState::QUITING;
			}

			if (INPUT->GetKey(SDLK_x))
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			if (INPUT->GetKey(SDLK_c))
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}


			break;

		case SDL_KEYUP:
			INPUT->SetKey(event.key.keysym.sym, false);
			break;
		case SDL_MOUSEMOTION:
			INPUT->MoveMouse(glm::ivec2(event.motion.xrel, event.motion.yrel));
			m_EntityManager->GetEntity("SceneEntity")->GetComponent<ControllerComponent>()->SetMouseMotion();
			break;
		}
	}
}
void Application::Render()
{
	for (auto itr = m_EntityManager->m_entities.begin(); itr != m_EntityManager->m_entities.end(); itr++)
	{
		if (m_renderType == RenderType::SHADOWPASS) 
		{
			glm::mat4 model = itr->second->GetTransform()->GetTransformationMatrix();
			ShadowShader->SetUniformMat4("model", model);
		}
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
	//m_EntityManager->GetEntity("Gun")->GetTransform()->SetPosition(m_EntityManager->GetEntity("SceneEntity")->GetTransform()->GetPosition() + (m_EntityManager->GetEntity("SceneEntity")->GetTransform()->GetForward() * 0.35f) + (m_EntityManager->GetEntity("SceneEntity")->GetTransform()->GetRight() * 0.2f));
	//m_EntityManager->GetEntity("Gun")->GetTransform()->SetRotation(m_EntityManager->GetEntity("SceneEntity")->GetTransform()->GetRotation());
	
	if (fireRate <= 0)
	{
		fireRate = 0;
	}
	else
	{
		fireRate -= deltaTime;
	}
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
void Application::InitialiseEntities()
{
	// Creating Usable Entity with camera component
	std::shared_ptr<Entity> SceneEntity = m_EntityManager->CreateEntity("SceneEntity");
	SceneEntity->GetTransform()->SetPosition(glm::vec3(-50.0f, 6.0f, 0.f));
	SceneEntity->AddComponent(new CameraComponent());
	SceneEntity->AddComponent(new ControllerComponent());

	std::shared_ptr<Entity> Platform = m_EntityManager->CreateEntity("Platform");

	Platform->AddComponent(new MeshRenderer(m_Resources->GetModel("Cube.obj"), 
											m_Resources->GetShader("BlinnPhong"),
											m_Resources->GetTexture("floor.jpg"))); //IF NO TEXTURE OR MATERIAL , DEFAULT WILL BE APPLIED
	
	Platform->GetTransform()->SetPosition(glm::vec3(-50.0f, -0.1f, -100.0f));
	Platform->AddComponent<RigidBody>();
	Platform->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 0.f, 100.f)));
	Platform->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	Platform->GetTransform()->SetScale(glm::vec3(100.f, 0.2f, 100.f));

	////KEEP
	std::shared_ptr<Entity> Building = m_EntityManager->CreateEntity("Building");
	Building->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Freigther_BI_Export.obj"), Resources::GetInstance()->GetShader("BlinnPhong")));
	Building->GetTransform()->SetPosition(glm::vec3(-50.0f, 0.1f, -100.f));
	Building->GetTransform()->RotateEulerAxis(80.f, glm::vec3(0.f, 1.f, 0.f));
	Building->GetTransform()->SetScale(glm::vec3(5.f, 5.0f, 5.0f));
	Building->AddComponent<RigidBody>();
	Building->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1, 1, 1)));
	Building->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

	////KEEP
	std::shared_ptr<Entity> man = m_EntityManager->CreateEntity("man");
	man->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("muro.obj"), Resources::GetInstance()->GetShader("BlinnPhong")));
	man->GetTransform()->SetPosition(glm::vec3(-70.0f, -0.1f, -40.f));
	man->GetTransform()->RotateEulerAxis(-45.f, glm::vec3(0.f, 1.f, 0.f));
	man->GetTransform()->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	man->AddComponent<RigidBody>();
	man->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 0.9f, 1.f)));

	////KEEP
	//std::shared_ptr<Entity> maya = m_EntityManager->CreateEntity("maya");
	//maya->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("maya.obj"), Resources::GetInstance()->GetShader("BlinnPhong")));
	//maya->GetTransform()->SetPosition(glm::vec3(15.0f, 3.0f, -20.f));
	//maya->GetTransform()->RotateEulerAxis(80.f, glm::vec3(0.f, 0.f, 0.f));
	//maya->GetTransform()->SetScale(glm::vec3(10.4f, 10.4f, 10.4f));
	//maya->AddComponent<RigidBody>();
	//maya->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 1.f, 1.f)));

	////KEEP
	std::shared_ptr<Entity> Joker = m_EntityManager->CreateEntity("Joker");
	Joker->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Joker.obj"), Resources::GetInstance()->GetShader("BlinnPhong")));
	Joker->GetTransform()->SetPosition(glm::vec3(-20.0f, 0.1f, -20.f));
	Joker->GetTransform()->RotateEulerAxis(0.f, glm::vec3(0.f, 1.f, 0.f));
	Joker->GetTransform()->SetScale(glm::vec3(0.11f, 0.11f, 0.11f));
	Joker->AddComponent<RigidBody>();
	Joker->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3( 1.f, 0.6f, 1.f)));

	////Will cause error
	std::shared_ptr<Entity> ERRORTEST = m_EntityManager->CreateEntity("Error Test");
	ERRORTEST->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel(""), Resources::GetInstance()->GetShader("BlinnPhong")));
	ERRORTEST->GetTransform()->SetPosition(glm::vec3(-120.0f, 1.0f, -40.f));
	ERRORTEST->GetTransform()->RotateEulerAxis(45.f, glm::vec3(0.f, 1.f, 0.f));
	ERRORTEST->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	std::shared_ptr<Entity> mustang_GT = m_EntityManager->CreateEntity("Car");
	mustang_GT->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("mustang_GT.obj"), Resources::GetInstance()->GetShader("BlinnPhong")));
	mustang_GT->GetTransform()->SetPosition(glm::vec3(-50.0f, 0.0f, -40.f));
	mustang_GT->GetTransform()->RotateEulerAxis(110.f, glm::vec3(1.f, 0.f, 0.f));
	mustang_GT->GetTransform()->RotateEulerAxis(180.f, glm::vec3(0.f, 1.f, 0.f));
	mustang_GT->GetTransform()->SetScale(glm::vec3(0.45f, 0.45f, 0.45f));
	mustang_GT->AddComponent<RigidBody>();
	mustang_GT->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.f, 1.f, 1.f)));



	////std::shared_ptr<Entity> Gun = m_EntityManager->CreateEntity("Gun");
	////Gun->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Portal Gun.obj"), Resources::GetInstance()->GetShader("BlinnPhong"), Resources::GetInstance()->GetTexture("lava.png")));
	////Gun->GetTransform()->SetPosition(SceneEntity->GetTransform()->GetPosition() + (SceneEntity->GetTransform()->GetForward()));
	//////RollerBall->GetTransform()->RotateEulerAxis(180.f, glm::vec3(0.f, 1.f, 0.f));
	////Gun->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	//////Gun->AddComponent<RigidBody>();
	//////Gun->GetComponent<RigidBody>()->Init(new SphereShape(2.5f));

	std::shared_ptr<Entity> PhysicsCube = m_EntityManager->CreateEntity("PhysicsCube");
	PhysicsCube->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Cube.obj"), Resources::GetInstance()->GetShader("BlinnPhong"),Resources::GetInstance()->GetTexture("lava.png")));
	PhysicsCube->GetTransform()->SetPosition(glm::vec3(0.0f, 15.0f, -40.f));
	PhysicsCube->GetTransform()->SetScale(glm::vec3(5.f, 5.f, 5.f));
	PhysicsCube->AddComponent<RigidBody>();
	PhysicsCube->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(5.1f, 5.1f, 5.1f)));
	
	
	//for (int i = 0; i < 40; i++)
	//{
	//	std::shared_ptr<Entity> a = m_EntityManager->CreateEntity("cube");
	//	a->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("sphere.obj"), Resources::GetInstance()->GetShader("BlinnPhong"), m_Resources->GetTexture("pink.png")));
	//	a->GetTransform()->SetPosition(glm::vec3(-70, 5.f * i, -100.f));
	//	a->GetTransform()->SetScale(glm::vec3(1, 1, 1));
	//	a->AddComponent<RigidBody>();
	//	a->GetComponent<RigidBody>()->Init(new SphereShape(1.f));
	//	a->GetComponent<RigidBody>()->m_rigidbody->setRestitution(0.0f);
	//}


}
