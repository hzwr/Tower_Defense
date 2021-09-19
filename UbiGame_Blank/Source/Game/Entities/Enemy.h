#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"


namespace Game
{
    class Enemy :
        public GameEngine::Entity
    {
    public:
        Enemy();
    private:
        void EntityUpdate() override;

        GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
        GameEngine::SpriteRenderComponent *m_outlineSpriteComp = nullptr;
        class MovementComponent *m_moveComp = nullptr;
        class NavComponent *m_navComp = nullptr;
        class HealthComponent *m_health = nullptr;

        float m_randomTurnTimer = 0.f;
    };
}