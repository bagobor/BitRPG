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


bool GameScreen::checkEvent(Event &event)
{
	// Catch key events
	
	if (event.type == Event::KeyPressed)
	{
		Event::KeyEvent keyEvent = event.key;
		
		// TEMP
		
		if (player)
		{
			if (keyEvent.code == Keyboard::Right)
				player->move(sf::Vector2u(1, 0));
			
			else if (keyEvent.code == Keyboard::Left)
				player->move(sf::Vector2u(-1, 0));
			
			else if (keyEvent.code == Keyboard::Up)
				player->move(sf::Vector2u(0, -1));
			
			else if (keyEvent.code == Keyboard::Down)
				player->move(sf::Vector2u(0, 1));
			
			else
				return false;
			
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
