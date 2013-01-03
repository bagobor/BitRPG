/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Character.h"
#include "EntityType.h"

using namespace bit;


Character::Character(shared_ptr<EntityType> entityType)
	: Entity(entityType)
{
	speed = 1.f / 8.f;
	moving = false;
}


void Character::advanceFrame(float deltaTime)
{
	if (!moving)
	{
		if (!movements.empty())
		{
			// Pop the first movement in the queue
			
			currentMovement = movements.front();
			movements.pop_front();
			
			moving = true;
		}
	}
	
	
	
	// Call the superclass's advanceFrame()
	
	Entity::advanceFrame(deltaTime);
}


void Character::addMovement(Movement movement)
{
	movements.push_back(movement);
}


void Character::clearMovements()
{
	movements.clear();
}
