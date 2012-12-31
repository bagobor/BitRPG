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
#include <boost/enable_shared_from_this.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class SharedSprite;
	class Entity;
	
	class Map : public sf::Drawable, public boost::enable_shared_from_this<Map>
	{
	public:
		Map(const sf::Vector2u &screenSize);
		void load(JSONValue &mapObject);
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void advanceFrame(float deltaTime);
		
		void addEntity(shared_ptr<Entity> entity, int zOrder);
		
		/**	Checks whether characters are blocked from walking
			onto a given coordinate
		*/
		// bool isSolid(int x, int y);
		
		shared_ptr<ContentManager> contentManager;
		shared_ptr<sf::View> mapView;
		
		/**	The Graphics on the map, used for fast access to rendering
			
			The multimap is ordered by the z-order of the sprite.
		*/
		std::multimap<int, shared_ptr<sf::Sprite> > sprites;
		
		/**	The pixel dimensions of the map tiles
		*/
		sf::Vector2u tileSize;
		
		/**	The the number of tiles spanning each dimension of the map
		*/
		sf::Vector2u mapSize;
		
	private:
		void loadTileset(JSONValue &tilesetObject);
		void loadLayer(JSONValue &layerObject, int zOrder);
		shared_ptr<sf::Texture> getTile(int gid);
		
		bool loaded;
		
		shared_ptr<sf::RenderTexture> mapTexture;
		shared_ptr<sf::Sprite> mapSprite;
		
		/**	Temporary storage of tile textures during the map loading process
			
			The map is ordered by the GID of the texture
		*/
		std::map<int, shared_ptr<sf::Texture> > tiles;
		
		/**	A complete list of entities to be rendered on the map
		*/
		std::vector<shared_ptr<Entity> > entities;
	};
}

#endif
