#include "HealthComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Entity.h"
#include "Game/Entities/Attack/Healthbar.h"
#include "Game/Entities/Attack/HealthbarFill.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/CollisionManager.h"
#include <cmath>
#include "Game/Entities/Attack/Laser.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "Game/Entities/PowerUp/Gear.h"


Game::HealthComponent::HealthComponent()
{

}

Game::HealthComponent::~HealthComponent()
{
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_healthbar);
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_healthbarFill);
}

void Game::HealthComponent::Update()
{
	const float deltaTime = GameEngine::GameEngineMain::GetTimeDelta();

	m_takeDamageCounter -= deltaTime;

	// During the construction, the component has not been added to the entity yet
	// We need to know to which entity this component belongs, so that we can
	// set healthbar entity's parent
	// Therefore, we init healthbar entities here
	if (!isInit)
	{
		m_healthbar = new Healthbar();
		GameEngine::GameEngineMain::GetInstance()->AddEntity(m_healthbar);

		m_healthbarFill = new HealthbarFill();


		if (m_hasParent)
		{
			m_healthbar->SetParent(GetEntity());
			m_healthbar->SetSize(sf::Vector2f(41.0f/32.0f, 5.0f/32.0f));
			m_healthbar->SetLocalPosOffset(sf::Vector2f(0, -16.0f));

			m_healthbarFill = new HealthbarFill();
			GameEngine::GameEngineMain::GetInstance()->AddEntity(m_healthbarFill);
			m_healthbarFill->SetParent(m_healthbar);
		}
		else
		{
			m_healthbar->SetSize(sf::Vector2f(82.0f, 10.0f));
			m_healthbar->SetPos(sf::Vector2f(902.0f, 702.0f));

			GameEngine::GameEngineMain::GetInstance()->AddEntity(m_healthbarFill);
			m_healthbarFill->SetParent(m_healthbar);
		}


		isInit = true;
	}

	m_healthbarFill->SetSize(sf::Vector2f(m_health/(m_maxHealth+0.001), 1.0f));	// have a really small value make sure we dont end up with size = 0, which leads to the sprite being rendered at orignal size
	m_healthbarFill->GetComponent<GameEngine::SpriteRenderComponent>()->UpdateSpriteParams();
	if (m_hasParent)
	{

		m_healthbarFill->SetLocalPosOffset(sf::Vector2f(-39.0f * (m_maxHealth - m_health)/m_maxHealth / 2, 0.0f));
	}
	else
	{
		m_healthbarFill->SetLocalPosOffset(sf::Vector2f(-78.0f * (m_maxHealth - m_health) / m_maxHealth / 2, 0.0f));

	}


	if (m_health <= 0.f)// if health less or equal to zero, destroy the entity
	{

		//add a gear
		Gear *gear = new Gear();
		gear->SetSize(sf::Vector2f(26.0f, 26.0f));
		gear->SetPos(GetEntity()->GetPos());
		GameEngine::GameEngineMain::GetInstance()->AddEntity(gear);

		// Add a score to the game board
		GameEngine::GameEngineMain::GetInstance()->GetGameBoard()->m_score += 10;


		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(GetEntity());


	}

	// check against laser
	auto pos = GetEntity()->GetPos();
	std::vector<GameEngine::Entity *> lasers = GameEngine::GameEngineMain::GetInstance()->GetEntitiesByTag("Laser");
	for (auto laser : lasers)
	{
		if (laser->IsActivated())
		{
			auto laserPos = laser->GetPos();
			auto laserRot = laser->GetRot();

			auto distance = abs(cosf(laserRot * 0.0174533) * (laserPos.y - pos.y)
				- sinf(laserRot * 0.0174533) * (laserPos.x - pos.x));
			distance = std::min(distance,
				abs(cosf((laserRot+90) * 0.0174533) * (laserPos.y - pos.y)
					- sinf((laserRot+90) * 0.0174533) * (laserPos.x - pos.x))
			);

			if (distance <= 12)
			{

					TakeDamage(5.0f);
					

				
			}
		}
	}

}

void Game::HealthComponent::TakeDamage(float damage /* = 0.1*/)
{


	if (m_health > 0.f && m_takeDamageCounter <= 0)
	{
		m_health -= damage;
		//printf("hit");
		m_takeDamageCounter = 1.0f;
	}
}
