#pragma once
#include "GameEngine\EntitySystem\Component.h"
#include "GameEngine/GameEngineMain.h"

namespace Game
{
    class MovementComponent :
        public GameEngine::Component
    {
    public:
        MovementComponent();
        virtual void Update() override;

        float GetAngularSpeed() const { return m_angularSpeed; }
        void SetAngularSpeed(float speed) { m_angularSpeed = speed; }

        float GetForwardSpeed() const { return m_speed; }
        void SetForwardSpeed(float speed) { m_speed = speed; m_slowDownPenaltyCounter = 0; }
        void SetMaxForwardSpeed(float speed) { m_maxSpeed = speed; }

        const sf::Vector2f &GetTravelDirection() const { return m_travelDir; }
        void SetTravelDirection(const sf::Vector2f &dir) { m_travelDir = dir; }

        const sf::Vector2f &GetFacingDirection() const { return m_facingDir; }
        void SetFacingDirection(sf::Vector2f &dir) { m_facingDir = dir; }

        void DisableRotation() { m_shouldRotate = false; }

    protected:
        bool m_shouldRotate = true;
        float m_angularSpeed = 10.0f;
        float m_speed = 20.0f;
        float m_maxSpeed = 20.0f;

        sf::Vector2f m_travelDir = sf::Vector2f(0.0f, 0.0f);
        sf::Vector2f m_facingDir = sf::Vector2f(0.0f, 0.0f);
        float m_slowDownPenaltyCounter = 0;

    };

}

