#pragma once
#include "GameEngine/EntitySystem/Entity.h"
namespace GameEngine { class SpriteRenderComponent; }
namespace Game
{

	class Laser : 
		public GameEngine::Entity
	{
	public:
		Laser(const sf::Vector2f &pos);
		void EntityUpdate() override;

	private:
		GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
		class MovementComponent *m_moveComp = nullptr;
		float m_cooldown = 1.0f;


	};
}