/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_GameScreen_h
#define BitRPG_GameScreen_h

#include "../Screen.h"
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	class Map;
	class JSONValue;
	
	class GameScreen : public Screen
	{
	public:
		GameScreen(const sf::Vector2u screenSize);
		
		void checkEvent(sf::Event &event);
		void advanceFrame(float deltaTime);
		
		void loadMap(JSONValue &mapObject);
		
		shared_ptr<ContentManager> contentManager;
		shared_ptr<Map> map;
		
	protected:
		void render() const;
	};
}

#endif
