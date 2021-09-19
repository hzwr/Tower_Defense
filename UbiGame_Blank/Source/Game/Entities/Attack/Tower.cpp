#include "Tower.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
//#include "Game/Entities/Pathfinding/Grid.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "Game/Components/AttackComponent/HealthComponent.h";
#include "Game/Components/AttackComponent/ShootingComponent.h"




Game::Tower::Tower(BulletType type, sf::Vector2f pos)
	:m_bulletType(type)
{
	// Sprite
	m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	switch (m_bulletType)
	{
	case Game::BulletType::ENormal:
		m_spriteComp->SetTexture(GameEngine::eTexture::Tower1);
		break;
	case Game::BulletType::EThunder:
		m_spriteComp->SetTexture(GameEngine::eTexture::Tower2);
		break;
	case Game::BulletType::ELaser:
		m_spriteComp->SetTexture(GameEngine::eTexture::Tower3);

		break;
	default:
		break;
	}
	m_spriteComp->SetZLevel(2);

	// Move
	//m_moveComp = static_cast<Game::MovementComponent *>(AddComponent<Game::MovementComponent>());



	// TODO: destructible tower
	//m_health = static_cast<HealthComponent *>(AddComponent<HealthComponent>());

	//m_outlineSpriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	//m_outlineSpriteComp->SetTexture(GameEngine::eTexture::HealthbarOutline);
	//m_outlineSpriteComp->SetZLevel(2);

	m_shootingComp = static_cast<Game::ShootingComponent *>(AddComponent<Game::ShootingComponent>());
	m_shootingComp->SetType(m_bulletType);

	SetPos(pos);
	SetSize(sf::Vector2f(40.0f, 40.0f));



}
