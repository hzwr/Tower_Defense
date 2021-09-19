#pragma once
#include "GameEngine\EntitySystem\Entity.h"

namespace GameEngine { class SpriteRenderComponent; }

namespace Game
{
    class Player :
        public GameEngine::Entity
    {
    public:
        Player();
        void EntityUpdate() override;
    protected:
        GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
        class InputComponent *m_inputComp = nullptr;
        class ShootingComponent *m_shootingComp = nullptr;
        class HealthComponent *m_health = nullptr;

    };

}

