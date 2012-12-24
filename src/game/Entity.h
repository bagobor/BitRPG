/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Entity_h
#define BitRPG_Entity_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	struct MapProperties;
	
	class Entity
	{
	public:
		Entity() {}
		
		void advanceFrame(float deltaTime);
		void setMapPosition(const sf::Vector2i &mapPostion);
		
		shared_ptr<sf::Sprite> sprite;
		shared_ptr<MapProperties> mapProperties;
		
	private:
		sf::Vector2i mapPostion;
		sf::Vector2f pixelOffset;
	};
}


#endif
