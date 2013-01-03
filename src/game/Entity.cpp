/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Entity.h"
#include "EntityType.h"
#include "../SharedSprite.h"
#include "Map.h"
#include <math.h>

using namespace bit;


Entity::Entity(shared_ptr<EntityType> entityType)
{
	this->entityType = entityType;
	
	// TEMP
	totalMoveFrames = 8;
	
	// Initialize default Entity fields
	
	positionUpdated = true;
	moveFrame = 0;
	animating = false;
	animationFrame = 0;
	animationSubFrame = 0;
	
	// Create a new Sprite
	
	sprite.reset(new SharedSprite);
	
	// Set the default frame
	
	sprite->setTexture(entityType->getDefaultFrame());
}


void Entity::advanceFrame(float deltaTime)
{
	// Query new movements
	
	if (!moving)
	{
		if (!destinations.empty())
		{
			currentDestination = destinations.front();
			destinations.pop_front();
			
			moving = true;
		}
	}
	
	if (!moving)
	{
		queryNextDestination();
	}
	
	// Handle sprite animation
	
	if (animating)
	{
		// Advance the animation
		
		animationSubFrame++;
		
		if (activeAnimation->subFrames <= animationSubFrame)
		{
			// Display the next frame
			
			animationFrame++;
			animationSubFrame = 0;
			
			if (activeAnimation->frames.size() <= animationFrame)
				animationFrame = 0;
			
			sprite->setTexture(activeAnimation->frames[animationFrame]);
		}
	}
	
	// Handle Entity movement
	
	if (moving)
	{
		moveFrame++;
		
		if (totalMoveFrames <= moveFrame)
		{
			// The Entity has reached its destination
			
			moveFrame = 0;
			position = currentDestination;
			
			moving = false;
		}
		
		positionUpdated = true;
	}
	
	// Handle position update
	
	if (positionUpdated && sprite)
	{
		shared_ptr<Map> map = mapWeak.lock();
		
		// Calculute the map position of the sprite
		
		float moveProportion = (float) moveFrame / totalMoveFrames;
		
		sf::Vector2f mapPosition;
		
		if (moving)
		{
			mapPosition.x = position.x + (currentDestination.x - position.x) * moveProportion;
			mapPosition.y = position.y + (currentDestination.y - position.y) * moveProportion;
		}
		else
		{
			mapPosition.x = position.x;
			mapPosition.y = position.y;
		}
		
		// Calculate the pixel location of the sprite
		
		sf::Vector2f pixelPosition;
		pixelPosition.x = mapPosition.x * map->tileSize.x + entityType->offsetPixels.x;
		pixelPosition.y = mapPosition.y * map->tileSize.y + entityType->offsetPixels.y;
		
		// Set the sprite position
		
		sprite->setPosition(pixelPosition);
		
		positionUpdated = false;
	}
}


void Entity::setPosition(const sf::Vector2i &position)
{
	this->position = position;
	
	// Reset the Entity's movement
	
	moveFrame = 0;
	moving = false;
	
	positionUpdated = true;
}


sf::Vector2i Entity::getPosition()
{
	return position;
}


void Entity::addDestination(const sf::Vector2i &destination)
{
	destinations.push_back(destination);
}


void Entity::clearDestinations()
{
	destinations.clear();
}


sf::Vector2i Entity::getCurrentDestination()
{
	if (moving)
		return currentDestination;
	
	else
		return position;
}


bool Entity::isMoving()
{
	return moving;
}


void Entity::setAnimating(bool enabled)
{
	animating = enabled;
	
	// Set the animation back to the first frame
	
	animationFrame = 0;
	animationSubFrame = 0;
}
