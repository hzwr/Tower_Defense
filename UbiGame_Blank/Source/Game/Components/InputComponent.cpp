#include "InputComponent.h"
#include "GameEngine/Util/InputManager.h"


void Game::InputComponent::Update()
{
	Component::Update();
	MovementComponent::Update();

	GameEngine::InputManager *input = GameEngine::InputManager::GetInstance();

	if (input->GetState().controller.IsConnected())
	{
		m_travelDir = input->GetState().controller.GetLeftStick();
		m_facingDir = input->GetState().controller.GetRightStick();
	}



}
