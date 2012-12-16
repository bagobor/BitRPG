/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapManager_h
#define BitRPG_MapManager_h

#include "JSONValue.h"

#include <boost/weak_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class MapTile;
	
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
		
		shared_ptr<ContentManager> contentManager;
		
	private:
		void loadTileset(JSONValue &tilesetObject);
		void loadLayer(JSONValue &layerObject, int zOrder);
		shared_ptr<MapTile> getTile(int gid);
		
		boost::shared_ptr<sf::RenderTexture> mapTexture;
		boost::shared_ptr<sf::Sprite> mapSprite;
		boost::shared_ptr<sf::View> mapView;
		
		// Drawable objects
		
		// TEMP
		std::vector<shared_ptr<sf::Sprite> > tileSprites;
		
		// <z-order, sprite>
		std::multimap<int, boost::weak_ptr<sf::Sprite> > sprites;
		
		// <gid, mapTile>
		std::multimap<int, shared_ptr<MapTile> > tiles;
	};
}

#endif
