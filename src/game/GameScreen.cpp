/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "GameScreen.h"
#include "Map.h"
#include "../SharedSprite.h"
#include "../JSONValue.h"
#include "Entity.h"

using namespace bit;
using namespace sf;


void GameScreen::preCheckEvents()
{
	// TEMP
	// Move the player based on currently pressed keys
	
	if (player && player->isMoving())
	{
		sf::Vector2i movement(0, 0);
		
		if (Keyboard::isKeyPressed(Keyboard::Right))
			movement = sf::Vector2i(1, 0);
		
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			movement = sf::Vector2i(-1, 0);
		
		else if (Keyboard::isKeyPressed(Keyboard::Up))
			movement = sf::Vector2i(0, -1);
		
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			movement = sf::Vector2i(0, 1);
		
		else
			return;
		
		// Add a destination to the player
		
		sf::Vector2i destination = player->getCurrentDestination() + movement;
		
		player->clearDestinations();
		player->addDestination(destination);
	}
}


bool GameScreen::checkEvent(Event &event)
{
	// Catch key events
	
	if (event.type == Event::KeyPressed)
	{
		Event::KeyEvent keyEvent = event.key;
		
		// TEMP
		// Move player
		
		if (player)
		{
			sf::Vector2i movement(0, 0);
			
			if (keyEvent.code == Keyboard::Right)
				movement = sf::Vector2i(1, 0);
			
			else if (keyEvent.code == Keyboard::Left)
				movement = sf::Vector2i(-1, 0);
			
			else if (keyEvent.code == Keyboard::Up)
				movement = sf::Vector2i(0, -1);
			
			else if (keyEvent.code == Keyboard::Down)
				movement = sf::Vector2i(0, 1);
			
			else
				return false;
			
			// Add a destination to the player
			
			sf::Vector2i destination = player->getCurrentDestination() + movement;
			
			player->clearDestinations();
			player->addDestination(destination);
			
			return true;
		}
	}
	
	// No events were caught
	
	return false;
}


void GameScreen::advanceFrame(float deltaTime)
{
	// If the map is loaded, advance its frame
	
	if (map)
	{
		map->advanceFrame(deltaTime);
	}
}


void GameScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (map)
	{
		map->draw(target, states);
	}
}


void GameScreen::loadMap(JSONValue &mapObject)
{
	// Create and initialize the Map
	
	map.reset(new Map(screenSize));
	map->contentManager = contentManager;
	map->load(mapObject);
}


void GameScreen::setPlayer(shared_ptr<Entity> player)
{
	this->player = player;
}
