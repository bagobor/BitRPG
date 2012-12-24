/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "GameScreen.h"
#include "Map.h"
#include "../JSONValue.h"
#include "Entity.h"

using namespace bit;
using namespace sf;


void GameScreen::checkEvent(Event &event)
{
	// Scrolls the view around using the arrow keys
	
	if (event.type == Event::KeyPressed)
	{
		Event::KeyEvent keyEvent = event.key;
		
		if (keyEvent.code == Keyboard::Right)
			;
		
		if (keyEvent.code == Keyboard::Left)
			;
		
		if (keyEvent.code == Keyboard::Up)
			;
		
		if (keyEvent.code == Keyboard::Down)
			;
	}
}


void GameScreen::advanceFrame(float deltaTime)
{
	// Iterate through each entity
	
	for (std::vector<shared_ptr<Entity> >::iterator entityIt =
		entities.begin(); entityIt != entities.end(); entityIt++)
	{
		// Advance the entity's frame
		
		(*entityIt)->advanceFrame(deltaTime);
	}
}


void GameScreen::loadMap(JSONValue &mapObject)
{
	// Create and initialize the Map
	
	map.reset(new Map(screenTexture->getSize()));
	map->contentManager = contentManager;
	map->load(mapObject);
	
	// Remove all entities from the GameScreen entities list
	
	entities.clear();
}


void GameScreen::addEntity(shared_ptr<Entity> entity, int zOrder)
{
	// Append the entity to the entities list
	
	entities.push_back(entity);
	
	if (map)
	{
		// Set the MapProperties of the entity
		
		entity->mapProperties = map->mapProperties;
		
		// Insert the entity's sprite into the map's sprites list
		
		std::pair<int, shared_ptr<sf::Sprite> > spritePair(zOrder, entity->sprite);
		map->sprites.insert(spritePair);
	}
}


void GameScreen::render() const
{
	if (map)
	{
		screenTexture->draw(*map);
	}
}
