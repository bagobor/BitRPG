/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_MapTile_h
#define BitRPG_MapTile_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class MapTile
	{
	public:
		shared_ptr<sf::Texture> texture;
	};
}

#endif
