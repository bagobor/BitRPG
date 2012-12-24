/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Map_h
#define BitRPG_Map_h

#include "../JSONValue.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class SharedSprite;
	struct MapProperties;
	
	class Map : public sf::Drawable
	{
	public:
		Map(const sf::Vector2u &screenSize);
		void load(JSONValue &mapObject);
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		/**	Checks whether the player is blocked from walking
			onto a given coordinate
		*/
		// bool checkCollision(int x, int y);
		
		shared_ptr<ContentManager> contentManager;
		shared_ptr<sf::View> mapView;
		
		shared_ptr<MapProperties> mapProperties;
		
		/**	The Graphics on the map, used for fast access to rendering
			
			The multimap is ordered by the z-order of the sprite.
		*/
		std::multimap<int, shared_ptr<sf::Sprite> > sprites;
		
	private:
		void loadTileset(JSONValue &tilesetObject);
		void loadLayer(JSONValue &layerObject, int zOrder);
		shared_ptr<sf::Texture> getTile(int gid);
		
		shared_ptr<sf::RenderTexture> mapTexture;
		shared_ptr<sf::Sprite> mapSprite;
		
		/**	Temporary storage of tile textures during the map loading process
			
			The map is ordered by the GID of the texture
		*/
		std::map<int, shared_ptr<sf::Texture> > tiles;
	};
	
	
	struct MapProperties
	{
		/**	The pixel dimensions of the map tiles
		*/
		sf::Vector2u tileSize;
		
		/**	The the number of tiles spanning each dimension of the map
		*/
		sf::Vector2u mapSize;
	};
}

#endif
