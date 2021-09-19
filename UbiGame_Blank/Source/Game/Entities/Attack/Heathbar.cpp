#include "Healthbar.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

Game::Healthbar::Healthbar()
{
	m_spriteComp = static_cast<GameEngine::SpriteRenderComponent *>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_spriteComp->SetTexture(GameEngine::eTexture::HealthbarOutline);
	m_spriteComp->SetZLevel(4);
}
