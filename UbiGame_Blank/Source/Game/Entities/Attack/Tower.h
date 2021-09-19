#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game/Entities/Attack/Bullet.h"


namespace Game
{
    class Tower :
        public GameEngine::Entity
    {
    public:
        Tower(BulletType type, sf::Vector2f pos);
    private:
        GameEngine::SpriteRenderComponent *m_spriteComp = nullptr;
        class ShootingComponent *m_shootingComp = nullptr;
        BulletType m_bulletType = BulletType::ENormal;
    };
}