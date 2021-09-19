#include "Laser.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/Components/MovementComponent.h"

Game::Laser::Laser(const sf::Vector2f &pos )
{
	SetEntityTag("Laser");

	// Sprite
	m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_spriteComp->SetTexture(GameEngine::eTexture::Laser);
	m_spriteComp->SetZLevel(4);

	m_moveComp = static_cast<Game::MovementComponent *>(AddComponent<Game::MovementComponent>());
	m_moveComp->SetAngularSpeed(10.0f);
	
	SetPos(pos);
}

void Game::Laser::EntityUpdate()
{
	const float deltaTime = GameEngine::GameEngineMain::GetTimeDelta();
	m_cooldown -= deltaTime;
	if (m_cooldown <= 0.f)
	{
		m_isActivated = !m_isActivated;
		m_cooldown = 1.0f;

		if (m_isActivated)
		{
			SetPos(GetPos() + sf::Vector2f(-2000, -2000));

		}
		else
		{
			SetPos(GetPos() + sf::Vector2f(+2000, +2000));

		}

	}
	


}
