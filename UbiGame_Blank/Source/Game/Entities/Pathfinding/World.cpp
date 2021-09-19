#include "World.h"

const std::vector<Game::Rectangle> Game::Wolrd::m_rectangles = {
	Game::Rectangle{ sf::Vector2i(0,93), sf::Vector2i(183,144), sf::Vector2i(1, 0) },
	Game::Rectangle{ sf::Vector2i(124,96), sf::Vector2i(180,256), sf::Vector2i(0, 1) },
	Game::Rectangle{ sf::Vector2i(39,228), sf::Vector2i(171,252), sf::Vector2i(-1, 0) },
	Game::Rectangle{ sf::Vector2i(36,228), sf::Vector2i(114,468), sf::Vector2i(0, 1) },
	Game::Rectangle{ sf::Vector2i(36,420), sf::Vector2i(250,472), sf::Vector2i(1, 0) },
	Game::Rectangle{ sf::Vector2i(186,416), sf::Vector2i(256,624), sf::Vector2i(0, 1) },
	Game::Rectangle{ sf::Vector2i(182,552), sf::Vector2i(404,626), sf::Vector2i(1, 0) },
	Game::Rectangle{ sf::Vector2i(360,78), sf::Vector2i(420,627), sf::Vector2i(0, -1) },
	Game::Rectangle{ sf::Vector2i(360,75), sf::Vector2i(558,162), sf::Vector2i(1, 0) },
	Game::Rectangle{ sf::Vector2i(504,81), sf::Vector2i(549,606), sf::Vector2i(0, 1) },
	Game::Rectangle{ sf::Vector2i(501,558), sf::Vector2i(891,612), sf::Vector2i(1, 0) },
	Game::Rectangle{ sf::Vector2i(858,444), sf::Vector2i(906,603), sf::Vector2i(0, -1) },
	Game::Rectangle{ sf::Vector2i(615,435), sf::Vector2i(906,504), sf::Vector2i(-1, 0) },
	Game::Rectangle{ sf::Vector2i(606,228), sf::Vector2i(657,495), sf::Vector2i(0, -1) },
	Game::Rectangle{ sf::Vector2i(615,228), sf::Vector2i(894,285), sf::Vector2i(1,0) },
	Game::Rectangle{ sf::Vector2i(834,225), sf::Vector2i(888,369), sf::Vector2i(0, 1) },
	Game::Rectangle{ sf::Vector2i(846,303), sf::Vector2i(996,357), sf::Vector2i(1, 0) },
		};

Game::OnPathInfo Game::Wolrd::isOnPath(const sf::Vector2f &pos)
{
	sf::Vector2i dir;
	bool isOnPath = false;

	for (auto &rec : m_rectangles)
	{
		if (pos.x > rec.topLeft.x		&&
			pos.x < rec.bottomRight.x 	&&
			pos.y > rec.topLeft.y 		&&
			pos.y < rec.bottomRight.y
			)
		{
			dir = rec.dirToTravel;
			isOnPath = true;
		};
	}
	return OnPathInfo{ isOnPath, dir };

	//return  OnPathInfo{ false, sf::Vector2i(0,0) };
}

