#include "Bullet.h"

#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/Components/MovementComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"



Game::Bullet::Bullet(BulletType type, const sf::Vector2f &pos, const sf::Vector2f &dir)
	:m_type(type)
{
	switch (type)
	{
	case Game::BulletType::ENormal:
		SetEntityTag("Bullet");

		break;
	case Game::BulletType::EThunder:
		SetEntityTag("Thunder");

		break;
	case Game::BulletType::ELaser:
		SetEntityTag("Laser");

		break;
	default:
		break;
	}

	switch (m_type)
	{
	case Game::BulletType::ENormal:
	{
		m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
		m_spriteComp->SetTexture(GameEngine::eTexture::Bullet1);
		m_spriteComp->SetZLevel(7);

		m_moveComp = static_cast<Game::MovementComponent *>(AddComponent<Game::MovementComponent>());
		m_moveComp->SetForwardSpeed(50.0f);
		m_moveComp->SetMaxForwardSpeed(50.0f);
		m_moveComp->SetTravelDirection(dir);
		break;
	}
	case Game::BulletType::EThunder:
	{
		m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
		m_spriteComp->SetTexture(GameEngine::eTexture::Bullet2);
		m_spriteComp->SetZLevel(7);

		m_moveComp = static_cast<Game::MovementComponent *>(AddComponent<Game::MovementComponent>());
		m_moveComp->SetForwardSpeed(50.0f);
		m_moveComp->SetMaxForwardSpeed(50.0f);
		m_moveComp->SetTravelDirection(dir);
		break;
	}
	default:
		break;
	}



	//Collisions
	AddComponent<GameEngine::CollidablePhysicsComponent>();

	SetPos(pos);
}

void Game::Bullet::EntityUpdate()
{
	m_counter += GameEngine::GameEngineMain::GetTimeDelta();

	if (m_counter >= 8)
	{
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
	}
}
