#pragma once
#pragma once
#include "GameEngine/EntitySystem/Entity.h"

namespace GameEngine { class SpriteRenderComponent; }
namespace Game
{
	class HealthbarFill : public GameEngine::Entity
	{
	public:
		HealthbarFill();
	private:
		GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
	};
}