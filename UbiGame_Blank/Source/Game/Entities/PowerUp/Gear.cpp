#include "Gear.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"


Game::Gear::Gear()
{
	SetEntityTag("Gear");

	m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_spriteComp->SetTexture(GameEngine::eTexture::Gear);
	m_spriteComp->SetZLevel(4);


	//Collisions
	AddComponent<GameEngine::CollidablePhysicsComponent>();

}

void Game::Gear::EntityUpdate()
{
	m_counter += GameEngine::GameEngineMain::GetTimeDelta();

	if (m_counter >= 14)
	{
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(this);
	}
}
