#include "CollidablePhysicsComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"

#include <vector>

#include "Game/Components/AttackComponent/HealthComponent.h";
#include "GameEngine/GameEngineMain.h"
#include "Game/Components/MovementComponent.h"


using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent()
{

}


CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnRemoveFromWorld();
}


void CollidablePhysicsComponent::Update()
{
	AABBRect intersection;
	AABBRect myBox = GetWorldAABB();

	
	// ----------------------------------------------------------------
	// Check with all collidables

	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();
	std::vector<CollidableComponent*>& pendingRemove = CollisionManager::GetInstance()->GetPendingRemove();

	// If the current collidable is already pending remove, dont check this!
	bool skip = std::find(pendingRemove.begin(), pendingRemove.end(), this) != pendingRemove.end();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		
		if (colComponent == this)
			continue;
		if (skip)
			continue;

		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			// Check if the collidable is enemy
			// check if the collidable is bullet 
			// destroy bullet on collision
			auto Entity = GetEntity();
			if (Entity->GetComponent<Game::HealthComponent>() != nullptr && (colComponent->GetEntity()->GetEntityTag() == "Bullet" || colComponent->GetEntity()->GetEntityTag() == "Bullet"))
			{
				if (colComponent->GetEntity()->GetEntityTag() == "Bullet")
				{
					Entity->GetComponent<Game::HealthComponent>()->TakeDamage(); //e0
				}
				else if(colComponent->GetEntity()->GetEntityTag() == "Thunder")
				{
					Entity->GetComponent<Game::MovementComponent>()->SetForwardSpeed(5.0f);
				}

				// This won't be removed after all entites get updated
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(colComponent->GetEntity()); // then the other one should be bullet 80
				CollisionManager::GetInstance()->AddToPendingRemove(colComponent);
				
				return;
			}
			else if (colComponent->GetEntity()->GetComponent<Game::HealthComponent>() != nullptr
				&& (Entity->GetEntityTag() == "Bullet" || (Entity->GetEntityTag() == "Thunder"))) // TODO: testing
			{
				if (Entity->GetEntityTag() == "Bullet")
				{
					colComponent->GetEntity()->GetComponent<Game::HealthComponent>()->TakeDamage();
				}
				else if(Entity->GetEntityTag() == "Thunder")
				{
					colComponent->GetEntity()->GetComponent<Game::MovementComponent>()->SetForwardSpeed(5.0f);
				}
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(Entity); // then the other one should be bullet
				CollisionManager::GetInstance()->AddToPendingRemove(this);

				return;
			}

			if (Entity->GetEntityTag() == "Gear" && colComponent->GetEntity()->GetEntityTag() == "Player")
			{
				GameEngine::GameEngineMain::GetInstance()->GetGameBoard()->AwardGear();
				GameEngine::GameEngineMain::GetInstance()->RemoveEntity(Entity);
				CollisionManager::GetInstance()->AddToPendingRemove(this);
			}

			//sf::Vector2f pos = GetEntity()->GetPos();
			//if (intersection.width < intersection.height)
			//{
			//	if (myBox.left < colideBox.left)
			//		pos.x -= intersection.width;
			//	else
			//		pos.x += intersection.width;
			//}
			//else
			//{
			//	if (myBox.top < colideBox.top)
			//		pos.y -= intersection.height;
			//	else
			//		pos.y += intersection.height;
			//}

			//GetEntity()->SetPos(pos);
		}
	}
}