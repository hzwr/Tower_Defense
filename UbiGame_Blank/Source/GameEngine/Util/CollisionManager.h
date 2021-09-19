#pragma once
#include <vector>

namespace GameEngine
{
	class CollidableComponent;

	class CollisionManager
	{
	public:		
		~CollisionManager();

		static CollisionManager* GetInstance() { if (!sm_instance) sm_instance = new CollisionManager(); return sm_instance; }

		void RegisterCollidable(CollidableComponent* collidable);
		void UnRegisterCollidable(CollidableComponent* collidable);
		//TODO - optimisation - instead of getcollidables, provide get near collidables so that we do not check collisions with all entities, just the ones that could potentially collide
		std::vector<CollidableComponent*>& GetCollidables() { return m_collidables; }
		std::vector<CollidableComponent*>& GetPendingRemove() { return m_pendingRemove; }

		void AddToPendingRemove(CollidableComponent *collidableToRemove)
		{
			m_pendingRemove.emplace_back(collidableToRemove);
		}
		void ClearPendingRemove()
		{
			m_pendingRemove.clear();
		}

	private:
		CollisionManager();
		static CollisionManager* sm_instance;

		std::vector<CollidableComponent*> m_collidables;
		std::vector<CollidableComponent *> m_pendingRemove = {};// clear this after object get destoryed
	};
}


