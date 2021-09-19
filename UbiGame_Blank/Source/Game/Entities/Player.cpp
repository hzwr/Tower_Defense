#include "Player.h"
#include "Game/Components/AttackComponent/ShootingComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/Components/InputComponent.h"
#include "GameEngine/Util/InputManager.h"
#include "Game/Entities/Attack/Tower.h"
#include "Game/Entities/Pathfinding/World.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "Game/Components/AttackComponent/HealthComponent.h";




Game::Player::Player()
{
	SetEntityTag("Player");

	// Sprite
	m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_spriteComp->SetTexture(GameEngine::eTexture::Eng);
	m_spriteComp->SetZLevel(2);

	m_health = static_cast<HealthComponent *>(AddComponent<HealthComponent>());
	m_health->DisableParent();
	m_health->SetMaxHealth(20.0f);


	// Input
	//m_movementComp = static_cast<Game::MovementComponent *>(AddComponent<Game::MovementComponent>());
	m_inputComp = static_cast<Game::InputComponent *>(AddComponent<Game::InputComponent>());
	m_inputComp->DisableRotation();
	m_inputComp->SetForwardSpeed(100.0f);
	m_inputComp->SetMaxForwardSpeed(100.0f);

	//m_shootingComp = static_cast<Game::ShootingComponent *>(AddComponent<Game::ShootingComponent>());

	//Collisions
	AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void Game::Player::EntityUpdate()
{
	GameEngine::InputManager *input = GameEngine::InputManager::GetInstance();
	auto gameboard = GameEngine::GameEngineMain::GetInstance()->GetGameBoard();
	auto &gears = gameboard->m_money;

	if (!Game::Wolrd::isOnPath(GetPos()).isOnPath)
	{
		if (gears >= 5 && input->GetState().controller.GetButtonState(0) == GameEngine::ButtonState::EReleased)
		{
			Tower *tower= new Tower(BulletType::ENormal,GetPos() + sf::Vector2f(-20.0f, -20.0f));
			tower->SetSize(sf::Vector2f(40.0f, 40.0f));
			GameEngine::GameEngineMain::GetInstance()->AddEntity(tower);
			gears -= 5;
		}
		else if (gears >= 10 && input->GetState().controller.GetButtonState(2) == GameEngine::ButtonState::EReleased)
		{
			Tower *tower = new Tower(BulletType::EThunder,GetPos() + sf::Vector2f(-20.0f, -20.0f));
			tower->SetSize(sf::Vector2f(40.0f, 40.0f));
			GameEngine::GameEngineMain::GetInstance()->AddEntity(tower);
			gears -= 10;

		}
		else if (gears >= 15 && input->GetState().controller.GetButtonState(1) == GameEngine::ButtonState::EReleased)	// Button B
		{
			Tower *tower = new Tower(BulletType::ELaser, GetPos() + sf::Vector2f(-20.0f, -20.0f));
			tower->SetSize(sf::Vector2f(40.0f, 40.0f));
			GameEngine::GameEngineMain::GetInstance()->AddEntity(tower);
			gears -= 15;

		}

	}

}



