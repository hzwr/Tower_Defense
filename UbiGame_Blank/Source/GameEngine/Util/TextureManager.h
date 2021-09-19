#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player = 0,
			PlayerEye = 1,
			Tile = 2,
			TilePath = 3,
			Bullet1 = 4,
			HealthbarOutline = 5,
			HealthbarFill = 6,
			Tower1 = 7,
			Tower2 = 8,
			Bullet2 = 9,
			Bullet3 = 10,
			Tower3,
			Gear,
			Laser,
			Eng,
			failBg,
			Tileset,
			BG,
			Particles,
			Count,
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player:			 return "ghost.png";
		case eTexture::PlayerEye:		 return "ghost-eye.png";
		case eTexture::Tile:			 return "tile.png";
		case eTexture::TilePath:		 return "tile-path.png";
		case eTexture::Bullet1:			 return "bullet-1.png";
		case eTexture::Bullet2:			 return "bullet-2.png";
		case eTexture::Bullet3:			 return "bullet-2.png";
		case eTexture::HealthbarOutline: return "healthbar-outline.png";
		case eTexture::HealthbarFill:	 return "healthbar-fill.png";
		case eTexture::Tileset:			 return "tileset.png";
		case eTexture::BG:				 return "bg.png";
		case eTexture::Particles:		 return "particles.png";
		case eTexture::Tower1:		     return "tower-1.png";
		case eTexture::Tower2:			 return "tower-2.png";
		case eTexture::Tower3:			 return "tower-3.png";
		case eTexture::Laser:			 return "laser.png";
		case eTexture::Gear:			 return "gear.png";
		case eTexture::Eng:				 return "eng.png";
		case eTexture::failBg:			 return "fail-bg.png";


		default:						 return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture);
}

