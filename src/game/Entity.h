/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Entity_h
#define BitRPG_Entity_h

#include "EntityType.h"
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

using boost::shared_ptr;
using boost::weak_ptr;


namespace bit
{
	class SharedSprite;
	class Map;
	
	class Entity
	{
	public:
		Entity(shared_ptr<EntityType> entityType);
		
		void advanceFrame(float deltaTime);
		void place(const sf::Vector2u &mapPostion);
		void move(const sf::Vector2u &deltaPosition);
		void quantize();
		
		shared_ptr<SharedSprite> sprite;
		weak_ptr<Map> mapWeak;
		
	protected:
		shared_ptr<EntityType> entityType;
		shared_ptr<EntityType::Animation> activeAnimation;
		
		/**	The coordinates of the Entity on the map
		*/
		sf::Vector2u mapPostion;
		
		/**	The fractional part of the map position
		*/
		sf::Vector2f tilePosition;
		
		bool hasMoved;
		
		int frame;
		int subFrame;
	};
}


#endif
