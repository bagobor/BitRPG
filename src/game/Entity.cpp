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
	this->entityType = entityType;
	
	hasMoved = true;
	frame = 0;
	subFrame = 0;
	
	// Create a new Sprite
	
	sprite.reset(new SharedSprite);
	
	// TEMP
	
	activeAnimation = entityType->getAnimation("idle");
	printf("%d frames\n", (int) activeAnimation->frames.size());
	
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
	
	if (hasMoved && sprite)
	{
		shared_ptr<Map> map = mapWeak.lock();
		
		// Calculate the pixel location of the sprite
		
		sf::Vector2f pixelPosition;
		pixelPosition.x = (int) (mapPostion.x * map->tileSize.x +
			tilePosition.x * map->tileSize.x + entityType->offsetPixels.x);
		pixelPosition.y = (int) (mapPostion.y * map->tileSize.y +
			tilePosition.y * map->tileSize.y + entityType->offsetPixels.y);
		
		// Set the sprite position
		
		sprite->setPosition(pixelPosition);
		
		hasMoved = false;
	}
}


void Entity::place(const sf::Vector2u &mapPostion)
{
	this->mapPostion = mapPostion;
	
	hasMoved = true;
}


void Entity::move(const sf::Vector2u &deltaPosition)
{
	mapPostion += deltaPosition;
	
	hasMoved = true;
}


void Entity::quantize()
{
	// Set the fractional part to zero
	
	tilePosition = sf::Vector2f(0.0f, 0.0f);
}
