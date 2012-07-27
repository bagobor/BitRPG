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
}


void DisplayManager::openWindow(JSONValue &windowObject)
{
	if (window)
		throw bit::Exception("Window is already opened");
	
	// Extract all the JSON data
	
	int width = windowObject["width"].toInteger();
	int height = windowObject["height"].toInteger();
	int zoom = windowObject["zoom"].toInteger();
	int framerate = windowObject["framerate"].toInteger();
	std::string title = windowObject["title"].toString();
	
	// Validate the config file
	
	if (width <= 0 || height <= 0)
		throw bit::Exception("Window size must be greater than zero");
	
	if (zoom <= 0)
		throw bit::Exception("Zoom must be greater than zero");
	
	this->zoom = zoom;
	
	// Create SFML RenderWindow
	
	VideoMode videoMode(width * zoom, height * zoom, 32);
	Uint32 windowStyle = Style::Titlebar | Style::Close;
	
	window.reset(new RenderWindow(videoMode, title.c_str(), windowStyle));
	
	if (!window)
		throw bit::Exception("Window could not be opened");
	
	// Set framerate limit
	
	window->setFramerateLimit(framerate);
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
