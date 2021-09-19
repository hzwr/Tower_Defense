#pragma once
#include "GameEngine/EntitySystem/Entity.h"

namespace GameEngine { class SpriteRenderComponent; }
namespace Game
{
	class Healthbar : public GameEngine::Entity
	{
	public:
		Healthbar();
	private:
		GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
	};
}