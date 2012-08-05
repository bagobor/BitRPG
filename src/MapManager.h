/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapManager_h
#define BitRPG_MapManager_h

#include "BitRPG.h"
#include "JSONValue.h"

#include <boost/weak_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class MapTile;


namespace bit
{
	class MapManager : public sf::Drawable
	{
	public:
		MapManager();
		
		void initSize(int pixelWidth, int pixelHeight);
		void loadMap(JSONValue &mapObject);
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		// void addEntity(EntityPtr entity, int zOrder);
		
		// Pixel dimensions of map tile
		int tileWidth, tileHeight;
		
		// Tile dimensions of map
		int mapWidth, mapHeight;
		
		/**
		 * Checks whether the player is blocked from walking
		 * onto a given coordinate
		 */
		bool isWall(int x, int y);
		
		ContentManagerPtr contentManager;
		
	private:
		void loadTileset(JSONValue &tilesetObject);
		void loadLayer(JSONValue &layerObject, int zOrder);
		MapTilePtr getTile(int gid);
		
		boost::shared_ptr<sf::RenderTexture> mapTexture;
		boost::shared_ptr<sf::Sprite> mapSprite;
		boost::shared_ptr<sf::View> mapView;
		
		// Drawable objects
		
		// TEMP
		std::vector<sf::SpritePtr> tileSprites;
		
		// <z-order, sprite>
		std::multimap<int, boost::weak_ptr<sf::Sprite> > sprites;
		
		// <gid, mapTile>
		std::multimap<int, MapTilePtr> tiles;
	};
}

#endif
