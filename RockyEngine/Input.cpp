#include "pch.h"
#include "Input.h"
Input* Input::m_instance = nullptr;
Input::Input()
{
}
void Input::InitGamePads()
{
	for (int i = 0; i < SDL_NumJoysticks(); i++)				//iterate throught the joysticks connected
	{
		if (SDL_IsGameController(i))						// if the joystick is detected to be a gamepad
		{
			m_gamePad = SDL_GameControllerOpen(i);	 // set to useable gamepad
			m_gamePad_Active = true;
			LOG_DEBUG("GAMEPAD CONNECTED");
			break;												//break because we only want one.
		}
	}
}
void Input::UpdateGamePads(SDL_Event event)
{
	switch (event.type) // switch throgh sdl poll events checking the event type
	{
		case SDL_CONTROLLERBUTTONDOWN:
			break;
		case SDL_CONTROLLERAXISMOTION: //check for motion
		if (event.caxis.which == 0) // check which controller index
		{
			if (event.caxis.axis == C_STICK::left_x) // get the stick & axis
			{
				if (event.caxis.value < -deadZone) // test against a deadzone 
				{
					X_Axis_Left = -1;  // if the condition is met change the value 
				}
				else if (event.caxis.value > deadZone)
				{
					X_Axis_Left = 1;
				}
				else
				{
					X_Axis_Left = 0;
				}
			}
			if (event.caxis.axis == C_STICK::left_y)
			{
				if (event.caxis.value < -deadZone)
				{
					Y_Axis_Left = -1;
				}
				else if (event.caxis.value > deadZone)
				{
					Y_Axis_Left = 1;
				}
				else
				{
					Y_Axis_Left = 0;
				}
			}

			if (event.caxis.axis == C_STICK::right_x)
			{
				if (event.caxis.value < -deadZone)
				{
					Y_Axis_Right = -1;
				}
				else if (event.caxis.value > deadZone)
				{
					Y_Axis_Right = 1;
				}
				else
				{
					Y_Axis_Right = 0;
				}
			}

			if (event.caxis.axis == C_STICK::right_y)
			{
				if (event.caxis.value < -deadZone)
				{
					X_Axis_Right = -1;
				}
				else if (event.caxis.value > deadZone)
				{
					X_Axis_Right = 1;
				}
				else
				{
					X_Axis_Right = 0;
				}
			}
		}
		break;
	}

	gamePad_LeftStick = glm::vec2(X_Axis_Left, Y_Axis_Left); // update the left and right stick coordinates 
	gamePad_RightStick = glm::vec2(X_Axis_Right, Y_Axis_Right);
}
Input* Input::GetInstance()
{
	if (m_instance == nullptr) //singleton to only allow one instance of input
	{
		m_instance = new Input();
	}
	return m_instance;
}
void Input::SetKey(SDL_Keycode key, bool state)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK) // check the key against the value of caps
	{
		index = (key - SDLK_SCANCODE_MASK) + 128; // if its more or less then re adjust to see if key is in rang of usable characters
	}
	if (index < m_state.keys.size())
	{
		m_state.keys[index] = state;
	}
}

bool Input::GetKey(SDL_Keycode key)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}
	if (index < m_state.keys.size())
	{
		return m_state.keys[index];
	}
	else return false;
}
Input::~Input()
{
	SDL_GameControllerClose(0); // 
	m_gamePad = NULL;
}

