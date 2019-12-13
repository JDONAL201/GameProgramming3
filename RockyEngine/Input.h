#pragma once
#include "Common.h"
#include "InputState.h"

#define INPUT Input::GetInstance()

class Input
{
private:
	Input();
	static Input* m_instance;
	bool m_gamePad_Active;
	InputState m_state;
	glm::vec2 gamePad_LeftStick = glm::vec2(0.f,0.f);
	glm::vec2 gamePad_RightStick = glm::vec2(0.f, 0.f);
public:

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
	void SetGamePadActive(bool b) { m_gamePad_Active = b; }
	void Gamepad_LeftMotion(glm::vec2 motion)
	{
		gamePad_LeftStick = motion;
		std::cout << "X: " << gamePad_LeftStick.x << " Y: " << gamePad_LeftStick.y << std::endl;
	}

	void Gamepad_RightMotion(glm::vec2 motion)
	{
		gamePad_RightStick = motion;
	}
};

