#pragma once
#include <SFML/Window/Joystick.hpp>
#include "GameEngine\GameEngineMain.h"

namespace GameEngine
{
	static constexpr int MaxControllerButtonCount = 32;

	enum class ButtonState
	{
		ENone,
		EPressed,
		EReleased,
		EHeld
	};

	class ControllerState
	{
	public:
		friend class InputManager;

		ButtonState GetButtonState(unsigned int button) const;
		const sf::Vector2f &GetLeftStick() const { return m_leftStick; }
		const sf::Vector2f &GetRightStick() const { return m_rightStick; }
		float GetLeftTrigger() const { return m_leftTrigger; }
		float GetRightTrigger() const { return m_rightTrigger; }
		bool IsConnected() const { return m_isConnected; }
	private:
		unsigned int mCurrButtons[MaxControllerButtonCount];
		unsigned int mPrevButtons[MaxControllerButtonCount];
		sf::Vector2f m_leftStick = sf::Vector2f(0.0f, 0.0f);
		sf::Vector2f m_rightStick = sf::Vector2f(0.0f, 0.0f);
		float m_leftTrigger = 0.0f;
		float m_rightTrigger = 0.0f;
		bool m_isConnected = false;
	};

	class KeyboardState
	{
	public:
		friend class InputManager;
	private:

	};

	struct InputState
	{
		ControllerState controller;
		KeyboardState keyboard;
	};

	class InputManager
	{
	public:
		void Update();
		void BeforeUpdate();

		//void ProcessEvent(sf::Event)
		const InputState &GetState() const { return m_state; }

		~InputManager();
		static InputManager *GetInstance() { if (!sm_instance) sm_instance = new InputManager(); return sm_instance; }
	private:

		InputState m_state;

		InputManager();
		static InputManager *sm_instance;
		//sf::Joystick *m_controller = nullptr;     // Controller id = 0?
	};

}


