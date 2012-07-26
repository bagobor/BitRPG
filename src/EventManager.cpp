/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "EventManager.h"
#include <iostream>
 
 using namespace bit;
 using namespace sf;


void EventManager::checkEvents()
{
	if (!window)
		return;
	
	Event event;
	
	// Loop through each event
	
	while (window->pollEvent(event))
	{
		checkEvent(event);
	}
}


void EventManager::checkEvent(Event &event)
{
	std::cout << event.type << std::endl;
}
