/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_EventManager_h
#define BitRPG_EventManager_h

#include "BitRPG.h"
#include <SFML/Window.hpp>


namespace bit
{
	class EventManager
	{
	public:
		void checkEvents();
		void checkEvent(sf::Event &event);
		
		boost::shared_ptr<sf::Window> window;
	};
}

#endif
