/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "MapManager.h"
#include "ContentManager.h"
#include "Exception.h"
#include "Entity.h"
#include "MapTile.h"

#include <string>
#include <sstream>

using namespace bit;
using namespace sf;


MapManager::MapManager()
{
}


void MapManager::initSize(int width, int height)
{
	// Create the map view
	
	mapView.reset(new View);
	mapView->setSize(width, height);
	mapView->setCenter(0.0f, 0.0f);
	
	// Create the map texture
	
	mapTexture.reset(new RenderTexture);
	mapTexture->create(width, height);
	mapTexture->setView(*mapView);
	
	// Create the map sprite
	
	mapSprite.reset(new Sprite);
	mapSprite->setTexture(mapTexture->getTexture());
	
	
}


void MapManager::loadMap(JSONValue &mapObject)
{
	if (mapObject["orientation"].toString() != "orthogonal")
		throw bit::Exception("Map must be orthogonal");
	
	// Set the tile dimensions
	
	tileWidth = mapObject["tilewidth"].toInteger();
	tileHeight = mapObject["tileheight"].toInteger();
	
	mapWidth = mapObject["width"].toInteger();
	mapHeight = mapObject["height"].toInteger();
	
	if (tileWidth <= 0 || tileHeight <= 0)
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
}


void MapManager::draw(RenderTarget &target, RenderStates states) const
{
	mapTexture->clear();
	
	// Draw entities and tiles onto the map texture
	
	/*
	for (std::multimap<int, EntityPtr>::const_iterator entityIt =
		 entities.begin(); entityIt != entities.end(); entityIt++)
	{
		// Draw entity
		
		target.draw(*entityIt->second);
	}
	*/
	
	// Draw the tile sprites
	
	for (std::multimap<int, SpritePtr>::const_iterator layerIt =
			layerSprites.begin(); layerIt != layerSprites.end(); layerIt++)
	{
		mapTexture->draw(*layerIt->second);
	}
	
	// Draw the map sprite onto the window
	
	mapTexture->display();
	target.draw(*mapSprite, states);
}


bool MapManager::isWall(int x, int y)
{
	// TODO Implement this operation
	
	return false;
}


/*
void MapManager::addEntity(EntityPtr entity, int zOrder)
{
	entities.insert(std::pair<int, EntityPtr>(zOrder, entity));
}
*/


void MapManager::loadTileset(JSONValue &tilesetObject)
{
	// Extract most of the JSONValue data
	
	std::string imageFilename = tilesetObject["image"].toString();
	ImagePtr image = contentManager->loadImage(imageFilename);
	
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
		
		IntRect rect(margin + (tileWidth + spacing) * x,
				margin + (tileHeight + spacing) * y,
				tileWidth, tileHeight);
		
		TexturePtr texture(new Texture);
		texture->loadFromImage(*image, rect);
		
		// Create MapTile
		
		MapTilePtr tile(new MapTile);
		tile->texture = texture;
		
		// Add texture to vector
		
		tiles.insert(std::pair<int, MapTilePtr>(firstGid + index, tile));
	}
}


void MapManager::loadLayer(JSONValue &layerObject, int zOrder)
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
		
		// If gid is zero, don't make a sprite
		
		if (gid == 0)
			continue;
		
		int pixelX = (mapX + index % mapWidth) * tileWidth;
		int pixelY = (mapY + index / mapWidth) * tileHeight;
		
		// Create the sprite
		
		SpritePtr tileSprite(new Sprite);
		tileSprite->setTexture(*getTile(gid)->texture);
		tileSprite->setPosition(pixelX, pixelY);
		
		// Put the sprite in the layerSprites map
		
		layerSprites.insert(std::pair<int, SpritePtr>(zOrder, tileSprite));
	}
}


MapTilePtr MapManager::getTile(int gid)
{
	std::multimap<int, MapTilePtr>::iterator tileIt = tiles.find(gid);
	
	// Check if a tile with the gid exists
	
	if (tileIt == tiles.end())
	{
		std::stringstream message;
		message << "Tile #" << gid << " does not exist";
		throw bit::Exception(message.str());
	}
	
	return tileIt->second;
}
