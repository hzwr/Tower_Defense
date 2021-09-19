#pragma once
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		void Update();		
		bool IsGameOver() { return false; }

		void AwardGear() { m_money += 5; }
		
		//TODO: no time now. make this private later!
		int m_score = 0;
		int m_money = 15;

	private:
		void CreateBackGround();
		void CreateGameOverBackGround();

		GameEngine::Entity *m_backGround;

		float m_enemyGenCooldown = 2.0f;
		GameEngine::Entity *m_text = nullptr;
		GameEngine::Entity *m_scoreText = nullptr;
		GameEngine::Entity *m_finalScore = nullptr;

		class Player *m_player = nullptr;
		float timeElapsed = 0.0f;

		bool is_gameOver = false;



	};
}

