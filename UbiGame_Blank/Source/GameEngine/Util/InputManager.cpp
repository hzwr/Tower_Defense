#include "InputManager.h"
#include <iostream>

GameEngine::InputManager *GameEngine::InputManager::sm_instance = nullptr;

sf::Vector2f Filter2D(float inputX, float inputY);
float Filter1D(int input);

GameEngine::ButtonState GameEngine::ControllerState::GetButtonState(unsigned int button) const
{
	if (mPrevButtons[button] == 0)
	{
		if (mCurrButtons[button] == 0)
		{
			return ButtonState::ENone;
		}
		else
		{
			return ButtonState::EPressed;
		}
	}
	else // Prev state must be 1
	{
		if (mCurrButtons[button] == 0)
		{
			return ButtonState::EReleased;
		}
		else
		{
			return ButtonState::EHeld;
		}
	}
}
void GameEngine::InputManager::Update()
{
	m_state.controller.m_isConnected = sf::Joystick::isConnected(0);

	if (m_state.controller.m_isConnected)
	{
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		m_state.controller.m_leftStick = sf::Vector2f(Filter2D(x, y));
		x = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
		y = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
		m_state.controller.m_rightStick = sf::Vector2f(Filter2D(x, y));

		// Triggers
		x = sf::Joystick::getAxisPosition(0, sf::Joystick::Z); // left trigger and right trigger are Z-AXIS, left positive, right negative
		float filtered = Filter1D(x);
		if (filtered > 0)
		{
			m_state.controller.m_leftTrigger = filtered;
		}
		else
		{
			m_state.controller.m_rightTrigger = -filtered;
		}

		// Buttons
		for (int i = 0; i < MaxControllerButtonCount; i++)
		{
			m_state.controller.mCurrButtons[i] =
				sf::Joystick::isButtonPressed(0,
					i);
		}
	}
}

void GameEngine::InputManager::BeforeUpdate()
{
	// Controller
	memcpy(m_state.controller.mPrevButtons,
		m_state.controller.mCurrButtons,
		MaxControllerButtonCount);
}

GameEngine::InputManager::~InputManager()
{
}

GameEngine::InputManager::InputManager()
{
	// Controller
	memset(m_state.controller.mCurrButtons, 0,
		MaxControllerButtonCount);
	memset(m_state.controller.mPrevButtons, 0,
		MaxControllerButtonCount);
}


// ------------------------------------------------------------------------------------
// Helper functions
template <typename T>
T Clamp(const T &value, const T &lower, const T &upper)
{
	return std::min(upper, std::max(lower, value));
}

// Return value between [-1,1]
sf::Vector2f Filter2D(float x, float y)
{
	const float DeadZone = 20.0f;
	const float Max = 100.0f;

	sf::Vector2f dir = sf::Vector2f(x, y);

	float lengthSq = dir.x * dir.x + dir.y * dir.y;
	float deadZoneSq = 400.0f;

	if (lengthSq < deadZoneSq)
	{
		dir = sf::Vector2f(0.0f, 0.0f);	// ignore drift
	}
	else
	{
		float length = sqrt(lengthSq);
		float f = (length - DeadZone) / (Max - DeadZone);
		f = Clamp(f, 0.0f, 1.0f);	// TODO: might need to normalize instad of clamp it
		dir *= f / length;
	}

	return dir;
}

float Filter1D(int input)
{
	const int DeadZone = 20;
	const int Max = 100;

	float finalInput = 0.0f;

	int absInput = abs(input);

	if (absInput > DeadZone)
	{
		finalInput = static_cast<float>(absInput - DeadZone) / (Max - DeadZone);
		finalInput = input > 0 ? finalInput : -1.0f * finalInput; // restore the sign
		finalInput = Clamp(finalInput, -1.0f, 1.0f);
	}

	return finalInput;
}
