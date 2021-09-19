#pragma once
#include "GameEngine\EntitySystem\Entity.h"

namespace GameEngine { class SpriteRenderComponent; }

namespace Game
{
    enum class BulletType
    {
        ENormal,
        EThunder,
        ELaser
    };

    class Bullet :
        public GameEngine::Entity
    {
    public:
        Bullet(BulletType type, const sf::Vector2f &pos, const sf::Vector2f &dir);

    private:
        void EntityUpdate() override;

        GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
        class MovementComponent *m_moveComp = nullptr;
        float m_counter = 0;
        BulletType m_type = BulletType::ENormal;
    };

}

