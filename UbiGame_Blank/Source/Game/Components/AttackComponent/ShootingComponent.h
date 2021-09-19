#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "Game/Entities/Attack/Bullet.h"

namespace Game
{
    class ShootingComponent :
        public GameEngine::Component
    {
    public:
        ShootingComponent();
        void SetType(BulletType type) { m_bulletType = type; }
        BulletType GetType() const { return m_bulletType; }
        void Update() override;
    private:
        float m_coolDownTimer = 3;
        BulletType m_bulletType = BulletType::ENormal;

        // For thunder bullets
        int m_bulletCount = 10;
        float m_fromAngle = 0.0f;
        float m_toAngle = 355.0f;

        bool isLaserExist = false; // if bullet type is laser, updating it only change the prop of the laser
        static constexpr float TWOPI = 6.28318530718f;
    };
}

