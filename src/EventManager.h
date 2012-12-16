/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_EventManager_h
#define BitRPG_EventManager_h

#include "BitRPG.h"
#include <SFML/Window.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class EventManager
	{
	public:
		void checkEvents();
		
		shared_ptr<Window> displayManager;
		boost::shared_ptr<sf::Window> window;
		
	private:
		void checkEvent(sf::Event &event);
	};
}

#endif
