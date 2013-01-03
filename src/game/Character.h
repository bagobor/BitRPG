/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Character_h
#define BitRPG_Character_h

#include "Entity.h"
#include <deque>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class EntityType;
	// class CharacterType;
	
	class Character : public Entity
	{
	public:
		Character(shared_ptr<EntityType> entityType);
		// Character(shared_ptr<CharacterType> characterType);
		
		void advanceFrame(float deltaTime);
		
		enum Movement
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		
		void addMovement(Movement movement);
		void clearMovements();
		
	private:
		std::deque<Movement> movements;
		float speed;
		bool moving;
		Movement currentMovement;
	};
}


#endif
