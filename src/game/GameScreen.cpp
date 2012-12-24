/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "GameScreen.h"
#include "Map.h"
#include "../JSONValue.h"
#include <stdio.h>

using namespace bit;
using namespace sf;


GameScreen::GameScreen(const Vector2u screenSize) : Screen(screenSize)
{
	map.reset(new Map(screenSize));
}


void GameScreen::checkEvent(Event &event)
{
	// TEMP
	// Scrolls the view around using the arrow keys
	
	if (event.type == Event::KeyPressed)
	{
		Event::KeyEvent keyEvent = event.key;
		float speed = 8.0f;
		
		if (keyEvent.code == Keyboard::Right)
			map->mapView->move(speed, 0.0f);
		
		if (keyEvent.code == Keyboard::Left)
			map->mapView->move(-speed, 0.0f);
		
		if (keyEvent.code == Keyboard::Up)
			map->mapView->move(0.0f, -speed);
		
		if (keyEvent.code == Keyboard::Down)
			map->mapView->move(0.0f, speed);
	}
}


void GameScreen::advanceFrame(float deltaTime)
{
	// Advance the map's frame
	
	map->advanceFrame(deltaTime);
}


void GameScreen::render() const
{
	screenTexture->draw(*map);
}


void GameScreen::loadMap(JSONValue &mapObject)
{
	// This should be moved somewhere else when Manager handling is improved.
	
	map->contentManager = contentManager;
	map->load(mapObject);
}
