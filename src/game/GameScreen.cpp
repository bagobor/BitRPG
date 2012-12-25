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


bool GameScreen::checkEvent(Event &event)
{
	// Catch key events
	
	if (event.type == Event::KeyPressed)
	{
		Event::KeyEvent keyEvent = event.key;
		shared_ptr<Entity> player = entities[0];
		
		if (keyEvent.code == Keyboard::Right)
			player->move(sf::Vector2f(0.5f, 0));
		
		else if (keyEvent.code == Keyboard::Left)
			player->move(sf::Vector2f(-0.5f, 0));
		
		else if (keyEvent.code == Keyboard::Up)
			player->move(sf::Vector2f(0, -0.5f));
		
		else if (keyEvent.code == Keyboard::Down)
			player->move(sf::Vector2f(0, 0.5f));
		
		else
			return false;
	}
	
	// No events were caught
	
	else
	{
		return false;
	}
	
	return true;
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
