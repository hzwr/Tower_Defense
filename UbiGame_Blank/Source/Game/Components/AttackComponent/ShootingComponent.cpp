#include "ShootingComponent.h"
#include "GameEngine/Util/InputManager.h"
#include <cmath>
#include "Game/Entities/Attack/Laser.h"

Game::ShootingComponent::ShootingComponent()
{

}

void Game::ShootingComponent::Update()
{
	GameEngine::InputManager *input = GameEngine::InputManager::GetInstance();

	const float deltaTime = GameEngine::GameEngineMain::GetTimeDelta();
	m_coolDownTimer -= deltaTime;

	if (input->GetState().controller.IsConnected())
	{

		switch (m_bulletType)
		{
		case BulletType::ENormal:
		{
			if (m_coolDownTimer <= 0)
				//if (m_coolDownTimer <= 0 && input->GetState().controller.GetRightTrigger() > 0.25f)
				//if (m_coolDownTimer <= 0 && input->GetState().controller.GetButtonState(0) == GameEngine::ButtonState::EReleased)
			{
				Bullet *bullet = new Bullet(
					BulletType::ENormal,
					GetEntity()->GetPos() + sf::Vector2f(0.f, -17.f),
					sf::Vector2f(0.0f, -1.0f));
				bullet->SetSize(sf::Vector2f(3.0f, 3.0f));
				GameEngine::GameEngineMain::GetInstance()->AddEntity(bullet);

				bullet = new Bullet(
					BulletType::ENormal,
					GetEntity()->GetPos() + sf::Vector2f(0.f, -8.f),
					sf::Vector2f(0.0f, 1.0f));
				bullet->SetSize(sf::Vector2f(3.0f, 3.0f));
				GameEngine::GameEngineMain::GetInstance()->AddEntity(bullet);

				bullet = new Bullet(
					BulletType::ENormal,
					GetEntity()->GetPos() + sf::Vector2f(-13.f, -11.f),
					sf::Vector2f(-1.0f, 0.0f));
				bullet->SetSize(sf::Vector2f(3.0f, 3.0f));
				GameEngine::GameEngineMain::GetInstance()->AddEntity(bullet);

				bullet = new Bullet(
					BulletType::ENormal,
					GetEntity()->GetPos() + sf::Vector2f(12.f, -11.f),
					sf::Vector2f(1.0f, 0.0f));
				bullet->SetSize(sf::Vector2f(3.0f, 3.0f));
				GameEngine::GameEngineMain::GetInstance()->AddEntity(bullet);

				m_coolDownTimer = 1.5f;
			}
			break;
		}
		case BulletType::EThunder:
		{
			if (m_coolDownTimer <= 0)
				//if (m_coolDownTimer <= 0 && input->GetState().controller.GetRightTrigger() > 0.25f)
				//if (m_coolDownTimer <= 0 && input->GetState().controller.GetButtonState(0) == GameEngine::ButtonState::EReleased)
			{
				float step = (m_toAngle - m_fromAngle) / m_bulletCount;
				for (int i = 0; i < m_bulletCount; ++i)
				{
							
					float currentAngle = (m_fromAngle + i * step)/ 360 * TWOPI;
					auto dirVector = sf::Vector2f(
						sinf(currentAngle),
						cosf(currentAngle)
					);

					Bullet *bullet = new Bullet(
						BulletType::EThunder,
						GetEntity()->GetPos() + sf::Vector2f(-1.f, -13.f),
						dirVector);

					bullet->SetSize(sf::Vector2f(20.0f, 20.0f));
					GameEngine::GameEngineMain::GetInstance()->AddEntity(bullet);

				}

				m_coolDownTimer = 2;
			}
			break;
		}
		case BulletType::ELaser:
		{
			if (!isLaserExist)
			{

				Laser *laser= new Laser(
					GetEntity()->GetPos() + sf::Vector2f(-1.f, -14.f));
				GameEngine::GameEngineMain::GetInstance()->AddEntity(laser);
				isLaserExist = true;
			}

		
		}
		default:
			break;
		}
		//printf("%f",input->GetState().controller.GetLeftTrigger());
		

		
	}
}
