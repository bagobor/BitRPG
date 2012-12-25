/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Entity.h"
#include "../SharedSprite.h"
#include "Map.h"
#include <math.h>

using namespace bit;


Entity::Entity()
{
	hasMoved = true;
}


void Entity::advanceFrame(float deltaTime)
{
	if (hasMoved && sprite && mapProperties)
	{
		// Calculate the pixel location of the sprite
		
		sf::Vector2f pixelPosition;
		pixelPosition.x = mapPostion.x * mapProperties->tileSize.x;
		pixelPosition.y = mapPostion.y * mapProperties->tileSize.y;
		
		// Set the sprite position
		
		sprite->setPosition(pixelPosition);
		
		hasMoved = false;
	}
}


void Entity::place(const sf::Vector2f &mapPostion)
{
	this->mapPostion = mapPostion;
	
	hasMoved = true;
}


void Entity::move(const sf::Vector2f &deltaPosition)
{
	this->mapPostion += deltaPosition;
	
	hasMoved = true;
}


void Entity::quantize()
{
	// Round the map positions to the nearest integer map tile
	
	mapPostion.x = floorf(mapPostion.x + 0.5f);
	mapPostion.y = floorf(mapPostion.y + 0.5f);
}
