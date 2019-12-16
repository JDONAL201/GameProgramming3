#pragma once
#include "Common.h"
#include "InputState.h"

#define INPUT Input::GetInstance()
enum C_STICK {left_x,left_y,right_x,right_y};
class Input
{
private:
	Input();
	static Input* m_instance;
	bool m_gamePad_Active;
	InputState m_state;
	glm::vec2 gamePad_LeftStick = glm::vec2(0.f,0.f);
	glm::vec2 gamePad_RightStick = glm::vec2(0.f, 0.f);
	SDL_GameController* m_gamePad;
	double X_Axis_Left, Y_Axis_Left, X_Axis_Right, Y_Axis_Right;
	float deadZone = 8000;
	~Input();

public:

	void InitGamePads();
	void UpdateGamePads(SDL_Event event);

	static Input* GetInstance();
	void SetKey(SDL_Keycode key, bool state);
	bool GetKey(SDL_Keycode key); // will check if currently down
	
	glm::ivec2 GetMousePos() { return m_state.mousePos; }
	glm::ivec2 GetMouseDelta() { return m_state.mousePrev - m_state.mousePos; }
	void MoveMouse(glm::ivec2 delta)
	{
		m_state.mousePrev = m_state.mousePos;
		m_state.mousePos += delta; 
	}
	glm::vec2 GetGamepad_LeftMotion() { return gamePad_LeftStick; }
	glm::vec2 GetGamepad_RightMotion() { return gamePad_RightStick; }

	bool GamePadIsActive() { return m_gamePad_Active; }
};

