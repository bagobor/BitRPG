/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapState_h
#define BitRPG_MapState_h

#include "State.h"
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class MapManager;
	class JSONValue;
	
	class MapState : public State
	{
	public:
		MapState();
		
		void init(const sf::Vector2u size);
		void checkEvent(sf::Event &event);
		void advanceFrame(float deltaTime);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		shared_ptr<MapManager> getMapManager();
		void loadMap(JSONValue &mapObject);
		
		shared_ptr<ContentManager> contentManager;
		
	private:
		shared_ptr<MapManager> mapManager;
	};
}

#endif
