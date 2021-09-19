#include "HealthbarFill.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

Game::HealthbarFill::HealthbarFill()
{
	m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_spriteComp->SetTexture(GameEngine::eTexture::HealthbarFill);
	m_spriteComp->SetZLevel(3);
}
