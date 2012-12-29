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

using boost::shared_ptr;


namespace bit
{
	class SharedSprite;
	struct MapProperties;
	
	class Entity
	{
	public:
		Entity(shared_ptr<EntityType> entityType);
		
		void advanceFrame(float deltaTime);
		void place(const sf::Vector2f &mapPostion);
		void move(const sf::Vector2f &deltaPosition);
		void quantize();
		
		shared_ptr<SharedSprite> sprite;
		shared_ptr<MapProperties> mapProperties;
		
	private:
		shared_ptr<EntityType::Animation> activeAnimation;
		
		sf::Vector2f mapPostion;
		bool hasMoved;
		
		int frame;
		int subFrame;
	};
}


#endif
