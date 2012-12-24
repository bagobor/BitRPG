/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Entity.h"
#include "../SharedSprite.h"
#include "Map.h"

using namespace bit;


void Entity::advanceFrame(float deltaTime)
{
	if (sprite && mapProperties)
	{
		// Calculate the pixel location of the sprite
		
		sf::Vector2f pixelPosition;
		pixelPosition.x = mapPostion.x * mapProperties->tileSize.x;
		pixelPosition.y = mapPostion.y * mapProperties->tileSize.y;
		
		pixelPosition += pixelOffset;
		
		// Set the sprite position
		
		sprite->setPosition(pixelPosition);
	}
}


void Entity::setMapPosition(const sf::Vector2i &mapPostion)
{
	this->mapPostion = mapPostion;
}
