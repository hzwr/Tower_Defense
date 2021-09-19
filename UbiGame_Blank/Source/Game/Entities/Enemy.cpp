#include "Enemy.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "Game/Components/AttackComponent/HealthComponent.h";
#include "GameEngine/GameEngineMain.h"
#include "Game/Components/MovementComponent.h"
#include "Game/Entities/Pathfinding/World.h"



Game::Enemy::Enemy()
{
	m_randomTurnTimer = rand() % 2;

	SetEntityTag("Enemy");

	// Sprite
	m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_spriteComp->SetTexture(GameEngine::eTexture::Player);
	m_spriteComp->SetZLevel(2);

	// Move
	m_moveComp = static_cast<Game::MovementComponent *>(AddComponent<Game::MovementComponent>());
	m_moveComp->SetTravelDirection(sf::Vector2f(1.0f, 0.0f));
	m_moveComp->DisableRotation();

	//Collisions
	AddComponent<GameEngine::CollidablePhysicsComponent>();

	m_health = static_cast<HealthComponent *>(AddComponent<HealthComponent>());

	//m_outlineSpriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	//m_outlineSpriteComp->SetTexture(GameEngine::eTexture::HealthbarOutline);
	//m_outlineSpriteComp->SetZLevel(2);




}

void Game::Enemy::EntityUpdate()
{
	const float deltaTime = GameEngine::GameEngineMain::GetTimeDelta();

	auto nextDir = (sf::Vector2f)Game::Wolrd::isOnPath(GetPos()).dirToTravel;
	if (m_moveComp->GetTravelDirection() != nextDir)
	{
		if (m_randomTurnTimer < 0)
		{
			m_moveComp->SetTravelDirection(nextDir);
				m_randomTurnTimer = rand() % 2;
		}
		else
		{
			m_randomTurnTimer -= deltaTime;
		}

	}


	/*auto pos = GetPos();
	if (pos.x < 0 || pos.x > GameEngine::GameEngineMain::WINDOW_WIDTH || pos.y < 0 || pos.y >GameEngine::GameEngineMain::WINDOW_HEIGHT)
	{
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
	}*/

}
