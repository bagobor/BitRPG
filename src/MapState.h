/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_MapState_h
#define BitRPG_MapState_h

#include "BitRPG.h"
#include "State.h"
#include <SFML/Graphics.hpp>


namespace bit
{
	class MapState : public State
	{
	public:
		MapState();
		
		void init(const sf::Vector2u size);
		void checkEvent(sf::Event &event);
		void advanceFrame(float deltaTime);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		MapManagerPtr getMapManager();
		void loadMap(JSONValue &mapObject);
		
		ContentManagerPtr contentManager;
		
	private:
		MapManagerPtr mapManager;
	};
}

#endif
