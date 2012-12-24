/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "EventManager.h"
#include "DisplayManager.h"
#include "Exception.h"

#include <stdio.h>
 
 using namespace bit;
 using namespace sf;


void EventManager::checkEvents()
{
	if (!window)
		throw bit::Exception("Cannot check events if window is not opened");
	
	Event event;
	
	// Loop through each event
	
	while (window->pollEvent(event))
	{
		checkEvent(event);
	}
}


void EventManager::checkEvent(Event &event)
{
	// Text event
	
	if (event.type == Event::TextEntered)
	{
		fputc(event.text.unicode, stdout);
		fflush(stdout);
	}
	
	// Key press event
	
	else if(event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Escape)
		{
			displayManager->closeWindow();
		}
	}
	
	// Close event
	
	else if (event.type == Event::Closed)
	{
		displayManager->closeWindow();
	}
}
