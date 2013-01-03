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
	class Entity;
	
	class GameScreen : public Screen
	{
	public:
		void preCheckEvents();
		bool checkEvent(sf::Event &event);
		void advanceFrame(float deltaTime);
		
		/**	Draws the graphics of this state to a render target
		*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		void loadMap(JSONValue &mapObject);
		
		void setPlayer(shared_ptr<Entity> player);
		
		shared_ptr<ContentManager> contentManager;
		shared_ptr<Map> map;
		
	private:
		shared_ptr<Entity> player;
	};
}

#endif
