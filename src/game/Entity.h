/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Entity_h
#define BitRPG_Entity_h

#include <deque>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

using boost::shared_ptr;
using boost::weak_ptr;


namespace bit
{
	class EntityType;
	class SharedSprite;
	class Map;
	struct Animation;
	
	class Entity
	{
	public:
		Entity(shared_ptr<EntityType> entityType);
		
		void advanceFrame(float deltaTime);
		
		void setPosition(const sf::Vector2i &position);
		sf::Vector2i getPosition();
		
		/**	Adds a destination to the queue
			
			The Entity will begin moving to the destination once the previous
			destinations are reached.
		*/
		void addDestination(const sf::Vector2i &destination);
		void clearDestinations();
		sf::Vector2i getCurrentDestination();
		bool isMoving();
		
		void setAnimating(bool enabled = true);
		
		shared_ptr<SharedSprite> sprite;
		weak_ptr<Map> mapWeak;
		
	protected:
		/**	Queries the next destination for subclasses
		*/
		virtual void queryNextDestination() {}
		
		bool moving;
		
		// "Hover" movement
		
		int moveFrame;
		int totalMoveFrames;
		
	private:
		shared_ptr<EntityType> entityType;
		
		/**	The coordinates of the Entity on the map
			
			The value (0, 0) refers to the top-left tile on the map screen.
		*/
		sf::Vector2i position;
		bool positionUpdated;
		
		/**	The current destination of Entity movement
		*/
		sf::Vector2i currentDestination;
		
		/**	Queue of map positions to move sequencially
		*/
		std::deque<sf::Vector2i> destinations;
		
		// Animation
		
		bool animating;
		shared_ptr<Animation> activeAnimation;
		
		/**	The current frame in the animation
		*/
		int animationFrame;
		
		/**	The number of window frames since the last animation frame
		*/
		int animationSubFrame;
	};
}


#endif
