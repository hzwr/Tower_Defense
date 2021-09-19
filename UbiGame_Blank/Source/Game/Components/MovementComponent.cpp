#include "MovementComponent.h"
#include "GameEngine\GameEngineMain.h"

Game::MovementComponent::MovementComponent()
{
}

void Game::MovementComponent::Update()
{
	Component::Update();



	const float deltaTime = GameEngine::GameEngineMain::GetTimeDelta();
	m_slowDownPenaltyCounter += deltaTime;

	if (m_slowDownPenaltyCounter >= 1)
	{
		SetForwardSpeed(m_maxSpeed);
		m_slowDownPenaltyCounter = 0;
	}

	constexpr float epsilon = 0.001f;

	constexpr float radToDegree = 57.2958f;

	if (m_shouldRotate)
	{
		float rotation = GetEntity()->GetRot(); 
		rotation += m_angularSpeed * deltaTime;
		GetEntity()->SetRotation(rotation);
	}

	if (m_speed >= epsilon)
	{
		sf::Vector2f pos = GetEntity()->GetPos();
		pos += m_speed * m_travelDir * deltaTime;
		GetEntity()->SetPos(pos);

	}



}
