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
		Entity();
		
		void advanceFrame(float deltaTime);
		void place(const sf::Vector2f &mapPostion);
		void move(const sf::Vector2f &deltaPosition);
		void quantize();
		
		shared_ptr<sf::Sprite> sprite;
		shared_ptr<MapProperties> mapProperties;
		
	private:
		sf::Vector2f mapPostion;
		bool hasMoved;
	};
}


#endif
