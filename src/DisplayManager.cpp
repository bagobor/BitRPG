/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "DisplayManager.h"
#include "EventManager.h"
#include "JSONValue.h"
#include "Exception.h"

#include <string>

using namespace bit;
using namespace sf;


DisplayManager::DisplayManager()
{
	eventManager.reset(new EventManager);
}


void DisplayManager::openWindow(JSONValue &windowObject)
{
	// Extract all the JSON data
	
	int width = windowObject["width"].toInteger();
	int height = windowObject["height"].toInteger();
	unsigned int framerate = windowObject["framerate"].toInteger();
	
	// Create SFML RenderWindow
	
	VideoMode videoMode(width, height, 32);
	std::string title = windowObject["title"].toString();
	Uint32 windowStyle = Style::Titlebar | Style::Close;
	
	window.reset(new RenderWindow(videoMode, title.c_str(), windowStyle));
	
	if (!window)
		throw bit::Exception("Window could not be opened");
	
	// Set framerate limit
	
	window->setFramerateLimit(framerate);
	
	eventManager->window = window;
}


void DisplayManager::closeWindow()
{
	running = false;
}


void DisplayManager::run()
{
	running = true;
	
	if (!window)
		throw bit::Exception("Window is not opened");
	
	while (running)
	{
		eventManager->checkEvents();
		render();
	}
}


void DisplayManager::render()
{
	window->clear(Color(128, 0, 128));
	
	// Render the window
	
	window->display();
}
