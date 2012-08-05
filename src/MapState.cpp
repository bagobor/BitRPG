/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "MapState.h"
#include "MapManager.h"
#include "JSONValue.h"

using namespace bit;
using namespace sf;


MapState::MapState()
{
	mapManager.reset(new MapManager);
}


void MapState::init(const Vector2u size)
{
	// Initialize the size of the MapManager
	
	mapManager->initSize(size.x, size.y);
}


void MapState::checkEvent(Event &event)
{
	// TODO
}


void MapState::advanceFrame(float deltaTime)
{
	// TODO
}


void MapState::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(*mapManager, states);
}


MapManagerPtr MapState::getMapManager()
{
	return mapManager;
}


void MapState::loadMap(JSONValue &mapObject)
{
	mapManager->contentManager = contentManager;
	
	if (mapManager)
		mapManager->loadMap(mapObject);
}
