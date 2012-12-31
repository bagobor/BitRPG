/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Map.h"
#include "../ContentManager.h"
#include "../Exception.h"
#include "Entity.h"
#include "../SharedSprite.h"

#include <string>
#include <sstream>

using namespace bit;


Map::Map(const sf::Vector2u &screenSize)
{
	// Create the map view
	
	mapView.reset(new sf::View);
	mapView->setSize(screenSize.x, screenSize.y);
	
	// TEMP
	// Set the center of the map view
	mapView->setCenter(screenSize.x / 2.0f, screenSize.y / 2.0f);
	
	// Create the map render texture
	
	mapTexture.reset(new sf::RenderTexture);
	mapTexture->create(screenSize.x, screenSize.y);
	mapTexture->setView(*mapView);
	
	// Create the map sprite with the map render texture
	
	mapSprite.reset(new sf::Sprite);
	mapSprite->setTexture(mapTexture->getTexture());
	
	loaded = false;
}


void Map::load(JSONValue &mapObject)
{
	// Check if the map is already loaded
	
	if (loaded)
		throw bit::Exception("Map is already loaded");
	
	// The map must be orthogonal
	
	if (mapObject["orientation"].toString() != "orthogonal")
		throw bit::Exception("Map must be orthogonal");
	
	// Set the tile dimensions
	
	tileSize.x = mapObject["tilewidth"].toInteger();
	tileSize.y = mapObject["tileheight"].toInteger();
	
	mapSize.x = mapObject["width"].toInteger();
	mapSize.y = mapObject["height"].toInteger();
	
	if (tileSize.x <= 0 || tileSize.y <= 0)
		throw bit::Exception("Tile dimensions must be greater than zero");
	
	// Build tilesets
	
	JSONValue tilesetArray = mapObject["tilesets"];
	int tilesetLength = tilesetArray.arrayLength();
	
	for (int index = 0; index < tilesetLength; ++index)
	{
		// Create tileset
		
		JSONValue tilesetObject = tilesetArray[index];
		loadTileset(tilesetObject);
	}
	
	// Build layers
	
	JSONValue layerArray = mapObject["layers"];
	int layerLength = layerArray.arrayLength();
	
	for (int index = 0; index < layerLength; ++index)
	{
		// Create layer
		
		JSONValue layerObject = layerArray[index];
		
		// The index (i.e. the order which the layer appears, zero-based)
		// will be its z-order number
		
		loadLayer(layerObject, index);
	}
	
	// Clear the temporary tiles map
	
	tiles.clear();
	
	loaded = true;
}


void Map::advanceFrame(float deltaTime)
{
	// Iterate through each entity
	
	for (std::vector<shared_ptr<Entity> >::iterator entityIt =
		entities.begin(); entityIt != entities.end(); entityIt++)
	{
		// Advance the entity's frame
		
		(*entityIt)->advanceFrame(deltaTime);
	}
}


void Map::addEntity(shared_ptr<Entity> entity, int zOrder)
{
	// Append the entity to the entities list
	
	entities.push_back(entity);
	
	// Set a weak pointer to this Map
	
	weak_ptr<Map> thisWeak(shared_from_this());
	entity->mapWeak = thisWeak;
	
	// Insert the entity's sprite into the sprites list
	
	std::pair<int, shared_ptr<sf::Sprite> > spritePair(zOrder, entity->sprite);
	sprites.insert(spritePair);
}


void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	mapTexture->clear();
	
	// Calculate the viewport of the map
	
	// TODO
	// This doesn't work correctly. The rectangle always starts at (0, 0)
	// and does not depend on the view position.
	
	sf::IntRect targetIntRect = target.getViewport(target.getView());
	sf::FloatRect targetRect(targetIntRect.left, targetIntRect.top,
		targetIntRect.width, targetIntRect.height);
	
	// Draw all the sprites ordered by their z-order, ascending
	
	for (std::multimap<int, shared_ptr<sf::Sprite> >::const_iterator spriteIt =
		sprites.begin(); spriteIt != sprites.end(); spriteIt++)
	{
		shared_ptr<sf::Sprite> sprite = spriteIt->second;
		
		// Check that the graphic exists
		
		if (sprite)
		{
			if (sprite->getGlobalBounds().intersects(targetRect))
			{
				// Draw the sprite onto the map
				
				mapTexture->draw(*sprite);
			}
		}
	}
	
	// Draw the map sprite onto the window
	
	mapTexture->display();
	target.draw(*mapSprite, states);
}


void Map::loadTileset(JSONValue &tilesetObject)
{
	// Extract the tileset data
	
	std::string imageFilename = tilesetObject["image"].toString();
	
	std::string name = tilesetObject["name"].toString();
	int firstGid = tilesetObject["firstgid"].toInteger();
	
	// int imageWidth = tilesetObject["imagewidth"].toInteger();
	// int imageHeight = tilesetObject["imageheight"].toInteger();
	
	sf::Vector2u tileSize;
	tileSize.x = tilesetObject["tilewidth"].toInteger();
	tileSize.y = tilesetObject["tileheight"].toInteger();
	int margin = tilesetObject["margin"].toInteger();
	int spacing = tilesetObject["spacing"].toInteger();
	
	// Load the tileset
	
	std::vector<shared_ptr<sf::Texture> > tilesetTextures =
		contentManager->loadTileset(imageFilename, tileSize, margin, spacing);
	
	int tilesetLength = tilesetTextures.size();
	
	// Iterate through each tile in the tileset
	
	for (int index = 0; index < tilesetLength; ++index)
	{
		shared_ptr<sf::Texture> tileTexture = tilesetTextures[index];
		
		// Add the texture to the tiles map
		
		std::pair<int, shared_ptr<sf::Texture> > tilePair(firstGid + index,
			tileTexture);
		tiles.insert(tilePair);
	}
	
}


void Map::loadLayer(JSONValue &layerObject, int zOrder)
{
	// Check that this is a tile layer
	
	std::string type = layerObject["type"].toString();
	
	if (type != "tilelayer")
		return;
	
	// Extract layer data
	
	std::string name = layerObject["name"].toString();
	
	int mapX = layerObject["x"].toInteger();
	int mapY = layerObject["y"].toInteger();
	int mapWidth = layerObject["width"].toInteger();
	int mapHeight = layerObject["height"].toInteger();
	int mapLength = mapWidth * mapHeight;
	
	// Extract tile data
	
	JSONValue dataArray = layerObject["data"];
	int dataLength = dataArray.arrayLength();
	
	// Check that the number of gids agrees with the map dimensions
	
	if (dataLength != mapLength)
		throw bit::Exception("Layer does not have the correct number of tiles");
	
	// Iterate through each tile
	
	for (int index = 0; index < dataLength; ++index)
	{
		int gid = dataArray[index].toInteger();
		
		// If gid is zero, don't make a Graphic
		
		if (gid == 0)
			continue;
		
		int pixelX = (mapX + index % mapWidth) * tileSize.x;
		int pixelY = (mapY + index / mapWidth) * tileSize.y;
		
		// Create the Graphic from the appropriate tile
		
		shared_ptr<SharedSprite> sprite(new SharedSprite);
		sprite->setTexture(getTile(gid));
		sprite->setPosition(pixelX, pixelY);
		
		// Insert the sprite in the graphics map
		
		std::pair<int, shared_ptr<SharedSprite> > spritePair(zOrder, sprite);
		sprites.insert(spritePair);
	}
}


shared_ptr<sf::Texture> Map::getTile(int gid)
{
	std::multimap<int, shared_ptr<sf::Texture> >::iterator tileIt = tiles.find(gid);
	
	// Check if a tile with the gid exists
	
	if (tileIt == tiles.end())
	{
		std::stringstream message;
		message << "Tile #" << gid << " does not exist";
		throw bit::Exception(message.str());
	}
	
	return tileIt->second;
}
