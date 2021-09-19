#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "Game\Entities\Player.h"
#include "Game\Entities\Enemy.h"

#include "GameEngine/EntitySystem/Components/TextRenderComponent.h"
#include "Game/Components/AttackComponent/HealthComponent.h"




using namespace Game;

GameBoard::GameBoard()
{
	m_player = new Player();
	m_player->SetPos(sf::Vector2f(16.0f, 16.0f));
	m_player->SetSize(sf::Vector2f(40.0f, 40.0f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_text = new GameEngine::Entity();
	m_text->SetPos(sf::Vector2f(860.0f, 738.0f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_text);
	GameEngine::TextRenderComponent *textRenderComponent = m_text->AddComponent<GameEngine::TextRenderComponent>();
	textRenderComponent->SetFont("ARCADECLASSIC.ttf");
	textRenderComponent->SetCharacterSizePixels(45);
	textRenderComponent->SetColor(sf::Color(132, 111, 100, 255));
	textRenderComponent->SetString("Player!");
	textRenderComponent->SetZLevel(3);

	m_scoreText = new GameEngine::Entity();
	m_scoreText->SetPos(sf::Vector2f(380.0f, 6.0f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_scoreText);
	GameEngine::TextRenderComponent *scoreTextRenderComponent = m_scoreText->AddComponent<GameEngine::TextRenderComponent>();
	scoreTextRenderComponent->SetFont("ARCADECLASSIC.ttf");
	scoreTextRenderComponent->SetCharacterSizePixels(45);
	scoreTextRenderComponent->SetColor(sf::Color(132, 111, 100, 255));
	scoreTextRenderComponent->SetString("Player!");
	scoreTextRenderComponent->SetZLevel(3);

	CreateBackGround();
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{
	if (m_player->GetComponent<Game::HealthComponent>() == nullptr)
	{
		if (!is_gameOver)
		{
		CreateGameOverBackGround();
		is_gameOver = true;

		}
	}

	const float deltaTime = GameEngine::GameEngineMain::GetTimeDelta();
	timeElapsed += deltaTime;

	if (m_enemyGenCooldown < 0 && timeElapsed <= 20)
	{
		auto enemy = new Enemy();
		enemy->SetPos(sf::Vector2f(2.0f, 122.0f+rand()%30-15.0f));
		enemy->SetSize(sf::Vector2f(32.0f, 32.0f));
		GameEngine::GameEngineMain::GetInstance()->AddEntity(enemy);
		m_enemyGenCooldown = 1.5f + rand() %2;
	}
	else if (m_enemyGenCooldown < 0 && timeElapsed > 20)
	{
		auto enemy = new Enemy();
		enemy->SetPos(sf::Vector2f(2.0f, 122.0f + rand() % 30 - 15.0f));
		enemy->SetSize(sf::Vector2f(32.0f, 32.0f));
		GameEngine::GameEngineMain::GetInstance()->AddEntity(enemy);
		m_enemyGenCooldown = 1.f + rand() % 2;
	}
	m_enemyGenCooldown -= deltaTime;

	// Update "money"
	m_text->GetComponent< GameEngine::TextRenderComponent>()->SetString(std::to_string(m_money));

	// Update score
	m_scoreText->GetComponent< GameEngine::TextRenderComponent>()->SetString("Score    " + std::to_string(m_score));
}

void GameBoard::CreateBackGround()
{
	GameEngine::Entity *bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent *render = bgEntity->AddComponent<GameEngine::SpriteRenderComponent>();
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(500.f, 400.f));
	bgEntity->SetSize(sf::Vector2f(1000.f, 800.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
}

void GameBoard::CreateGameOverBackGround()
{
	GameEngine::Entity *bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent *render = bgEntity->AddComponent<GameEngine::SpriteRenderComponent>();
	render->SetTexture(GameEngine::eTexture::failBg);
	render->SetZLevel(10);
	bgEntity->SetPos(sf::Vector2f(500.f, 400.f));
	bgEntity->SetSize(sf::Vector2f(1000.f, 800.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;

	m_finalScore= new GameEngine::Entity();
	m_finalScore->SetPos(sf::Vector2f(372.0f, 542.0f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_finalScore);
	GameEngine::TextRenderComponent *textRenderComponent = m_finalScore->AddComponent<GameEngine::TextRenderComponent>();
	textRenderComponent->SetFont("ARCADECLASSIC.ttf");
	textRenderComponent->SetCharacterSizePixels(45);
	textRenderComponent->SetColor(sf::Color(132, 111, 100, 255));
	textRenderComponent->SetString("Your Score " + std::to_string(m_score));
	textRenderComponent->SetZLevel(11);
}