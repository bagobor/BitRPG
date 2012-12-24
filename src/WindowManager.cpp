/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "WindowManager.h"
#include "Screen.h"
#include "JSONValue.h"
#include "Exception.h"

#include <SFML/Window.hpp>
#include <string>

using namespace bit;
using namespace sf;


WindowManager::WindowManager()
{
	screenSize = sf::Vector2u(0, 0);
}


WindowManager::~WindowManager()
{
	closeWindow();
}


void WindowManager::openWindow(JSONValue &windowObject)
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
	
	screenSize.x = width;
	screenSize.y = height;
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
	
	// Set miscellaneous window settings
	
	window->setKeyRepeatEnabled(true);
	window->setVisible(true);
	window->setVerticalSyncEnabled(false);
	
	// Create window view
	
	View windowView(window->getDefaultView());
	windowView.setCenter(width / 2.0f, height / 2.0f);
	windowView.zoom(1.0f / zoom);
	window->setView(windowView);
}


void WindowManager::closeWindow()
{
	if (window)
		window->close();
}


void WindowManager::run()
{
	if (!window)
		throw bit::Exception("Window is not created");
	
	// Run the display loop
	
	while (window && window->isOpen())
	{
		Event event;
		
		while (window->pollEvent(event))
		{
			// Close the window and stop the loop if the Close button was pressed
			
			if (event.type == Event::Closed)
			{
				closeWindow();
			}
			
			// Let the current state process the event
			
			if (activeScreen)
				activeScreen->checkEvent(event);
		}
		
		// Advance the state's frame
		
		if (activeScreen)
			activeScreen->advanceFrame(deltaTime);
		
		// Render the window
		
		render();
	}
}


void WindowManager::render()
{
	// Clear the screen with a black background
	
	window->clear(Color::Black);
	
	// Render the active screen to the render window
	
	if (activeScreen)
		window->draw(*activeScreen);
	
	// Flip the window's double buffer
	
	window->display();
}
