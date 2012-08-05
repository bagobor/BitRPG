/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "DisplayManager.h"
#include "EventManager.h"
#include "StateManager.h"
#include "State.h"
#include "JSONValue.h"
#include "Exception.h"
#include "MapState.h"
#include "MapManager.h"

#include "SplashState.h"
#include <SFML/Window.hpp>
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
	deltaTime = 1.0f / framerate;
	
	// Create window view
	
	windowView.reset(new View(window->getDefaultView()));
	windowView->setCenter(width / 2.0f, height / 2.0f);
	windowView->zoom(1.0f / zoom);
	window->setView(*windowView);
	
	// Initialize the MapManager size
	
	stateManager->initAllStates(window->getSize());
}


void DisplayManager::closeWindow()
{
	window->close();
}


void DisplayManager::run()
{
	if (!window)
		throw bit::Exception("Window is not created");
	
	// Run the display loop
	
	while (window->isOpen())
	{
		// Get the current state
		
		StatePtr currentState = stateManager->getCurrentState();
		
		Event event;
		
		while (window->pollEvent(event))
		{
			// Close the window and stop the loop if the Escape key was pressed
			
			if (event.type == Event::Closed)
			{
				closeWindow();
			}
			
			// Let the current state process the event
			
			if (currentState)
				currentState->checkEvent(event);
		}
		
		// Render the current state
		
		if (currentState)
			currentState->advanceFrame(deltaTime);
		
		render();
	}
}


void DisplayManager::render()
{
	window->clear(Color::Black);
	
	// Render window
	
	StatePtr currentState = stateManager->getCurrentState();
	
	if (currentState)
		window->draw(*currentState);
	
	window->setView(*windowView);
	window->display();
}
