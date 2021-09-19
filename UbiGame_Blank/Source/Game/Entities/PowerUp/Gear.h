#pragma once
#include "GameEngine\EntitySystem\Entity.h"

namespace GameEngine { class SpriteRenderComponent; }

namespace Game
{
	class Gear :
		public GameEngine::Entity

	{
	public:
		Gear();
		void EntityUpdate() override;

	private:
		GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
		float m_counter = 0;

	};

}