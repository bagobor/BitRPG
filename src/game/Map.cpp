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
	mapProperties.reset(new MapProperties);
	
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
}


void Map::load(JSONValue &mapObject)
{
	if (mapObject["orientation"].toString() != "orthogonal")
		throw bit::Exception("Map must be orthogonal");
	
	// Set the tile dimensions
	
	mapProperties->tileSize.x = mapObject["tilewidth"].toInteger();
	mapProperties->tileSize.y = mapObject["tileheight"].toInteger();
	
	mapProperties->mapSize.x = mapObject["width"].toInteger();
	mapProperties->mapSize.y = mapObject["height"].toInteger();
	
	if (mapProperties->tileSize.x <= 0 || mapProperties->tileSize.y <= 0)
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
}


void Map::advanceFrame(float deltaTime)
{
	for (std::vector<shared_ptr<Entity> >::iterator entityIt =
		entities.begin(); entityIt != entities.end(); entityIt++)
	{
		// Advance the entity's frame
		
		(*entityIt)->advanceFrame(deltaTime);
	}
}


void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	mapTexture->clear();
	
	// Draw all the sprites ordered by their z-order, ascending
	
	for (std::multimap<int, shared_ptr<sf::Sprite> >::const_iterator spriteIt =
		sprites.begin(); spriteIt != sprites.end(); spriteIt++)
	{
		shared_ptr<sf::Sprite> sprite = spriteIt->second;
		
		// Check that the graphic exists
		
		if (sprite)
		{
			// Draw the sprite onto the map
			
			mapTexture->draw(*sprite);
		}
	}
	
	// Draw the map sprite onto the window
	
	mapTexture->display();
	target.draw(*mapSprite, states);
}


void Map::addEntity(shared_ptr<Entity> entity, int zOrder)
{
	// Set the MapProperties of the entity
	
	entity->mapProperties = mapProperties;
	
	// Append the entity to the entities list
	
	entities.push_back(entity);
	
	// Insert the entity's sprite into the sprites list
	
	std::pair<int, shared_ptr<sf::Sprite> > spritePair(zOrder, entity->sprite);
	sprites.insert(spritePair);
}


void Map::loadTileset(JSONValue &tilesetObject)
{
	// Extract most of the JSONValue data
	
	std::string imageFilename = tilesetObject["image"].toString();
	shared_ptr<sf::Image> tilesetImage = contentManager->loadImage(imageFilename);
	
	std::string name = tilesetObject["name"].toString();
	int firstGid = tilesetObject["firstgid"].toInteger();
	
	int imageWidth = tilesetObject["imagewidth"].toInteger();
	int imageHeight = tilesetObject["imageheight"].toInteger();
	int tileWidth = tilesetObject["tilewidth"].toInteger();
	int tileHeight = tilesetObject["tileheight"].toInteger();
	int margin = tilesetObject["margin"].toInteger();
	int spacing = tilesetObject["spacing"].toInteger();
	
	// Check the math of the tileset dimensions
	
	if ((imageWidth + spacing - 2 * margin) % (spacing + tileWidth) != 0)
		throw bit::Exception("Tileset image '" + imageFilename +
				"' does not have a valid width");
	
	if ((imageHeight + spacing - 2 * margin) % (spacing + tileHeight) != 0)
		throw bit::Exception("Tileset image '" + imageFilename +
				"' does not have a valid height");
	
	// Create the map dimensions of the tileset.
	// These correspond to the number of tiles
	// across the image in each dimension.
	
	int mapWidth = (imageWidth + spacing - 2 * margin) / (spacing + tileWidth);
	int mapHeight = (imageHeight + spacing - 2 * margin) / (spacing + tileHeight);
	int mapLength = mapWidth * mapHeight;
	
	for (int index = 0; index < mapLength; ++index)
	{
		int x = index % mapWidth;
		int y = index / mapWidth;
		
		sf::IntRect rect(margin + (tileWidth + spacing) * x,
				margin + (tileHeight + spacing) * y,
				tileWidth, tileHeight);
		
		shared_ptr<sf::Texture> tileTexture(new sf::Texture);
		tileTexture->loadFromImage(*tilesetImage, rect);
		
		// Add texture to vector
		
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
		
		int pixelX = (mapX + index % mapWidth) * mapProperties->tileSize.x;
		int pixelY = (mapY + index / mapWidth) * mapProperties->tileSize.y;
		
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
