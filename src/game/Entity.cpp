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


Entity::Entity(shared_ptr<EntityType> entityType)
{
	hasMoved = true;
	frame = 0;
	subFrame = 0;
	
	// Create a new Sprite
	
	sprite.reset(new SharedSprite);
	
	// TEMP
	
	activeAnimation = entityType->getAnimation("idle");
	printf("%d\n", (int) activeAnimation->frames.size());
	
	sprite->setTexture(activeAnimation->frames[0]);
}


void Entity::advanceFrame(float deltaTime)
{
	// Advance the subframe
	
	subFrame++;
	
	if (activeAnimation->subFrames <= subFrame)
	{
		// Display the next frame
		
		frame++;
		subFrame = 0;
		
		if (activeAnimation->frames.size() <= frame)
			frame = 0;
		
		sprite->setTexture(activeAnimation->frames[frame]);
	}
	
	// Handle sprite movement
	
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
