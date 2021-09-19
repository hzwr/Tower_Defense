#pragma once
#include "GameEngine/EntitySystem/Component.h"

namespace GameEngine { class SpriteRenderComponent; }

namespace Game
{
	class HealthComponent : public GameEngine::Component
	{
	public:
		HealthComponent();
		~HealthComponent();

		void DisableParent() { m_hasParent = false; }
		void Update() override;
		void TakeDamage(float damage = 1);

		void SetMaxHealth(int health) { m_health = health; m_maxHealth = health; }
		int GetHealth() const { return m_health; }

	private:
		class Healthbar *m_healthbar = nullptr;
		class HealthbarFill *m_healthbarFill = nullptr;

		int m_health = 4;
		int m_maxHealth = 4;

		bool isInit = false;
		bool m_hasParent = true;

		float m_takeDamageCounter = 0;
	};
}
