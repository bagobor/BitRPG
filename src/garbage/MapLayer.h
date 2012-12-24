/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapLayer_h
#define BitRPG_MapLayer_h

#include "BitRPG.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace bit
{
	class MapLayer : public sf::Drawable
	{
	public:
		MapLayer();
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
	private:
		int mapWidth, mapHeight;
		int mapX, mapY;
		int zOrder;
		
		std::vector<sf::SpritePtr> mapSprites;
	};
}

#endif
