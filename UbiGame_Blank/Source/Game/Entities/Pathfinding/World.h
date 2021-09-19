#include <vector>
#include <SFML/System/Vector2.hpp>

namespace Game
{
	struct OnPathInfo
	{
		bool isOnPath = false;
		sf::Vector2i dirToTravel;
	};

	struct Rectangle
	{
		sf::Vector2i topLeft;
		sf::Vector2i bottomRight;
		sf::Vector2i dirToTravel; // indicate which way the object should travel in this rec

	};
	struct Wolrd
	{
		// Check if something is on the path (i.e. in one of the rectangles)
		static OnPathInfo isOnPath(const sf::Vector2f &pos);
	private:
		static const std::vector<Rectangle> m_rectangles;
	};
}