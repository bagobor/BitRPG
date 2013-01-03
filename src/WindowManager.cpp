/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "WindowManager.h"
#include "Screen.h"
#include "JSONValue.h"
#include "Exception.h"
#include "Console.h"

#include <SFML/Window.hpp>
#include <string>

using namespace bit;
using namespace sf;


WindowManager::WindowManager()
{
	screenSize = sf::Vector2u(0, 0);
	
	// Create the Console
	
	console.reset(new Console);
	
	consoleEnabled = false;
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
	
	sf::Vector2u screenSize;
	screenSize.x = windowObject["width"].toInteger();
	screenSize.y = windowObject["height"].toInteger();
	int zoom = windowObject["zoom"].toInteger();
	int framerate = windowObject["framerate"].toInteger();
	std::string title = windowObject["title"].toString();
	
	// Validate the config file
	
	if (screenSize.x <= 0 || screenSize.y <= 0)
		throw bit::Exception("Window size must be greater than zero");
	
	if (zoom <= 0)
		throw bit::Exception("Zoom must be greater than zero");
	
	this->screenSize = screenSize;
	this->zoom = zoom;
	
	// Create SFML RenderWindow
	
	VideoMode videoMode(screenSize.x * zoom, screenSize.y * zoom, 32);
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
	windowView.setCenter(screenSize.x / 2.0f, screenSize.y / 2.0f);
	windowView.zoom(1.0f / zoom);
	window->setView(windowView);
	
	// Create the screen texture
	
	screenTexture.reset(new sf::RenderTexture);
	screenTexture->create(screenSize.x, screenSize.y);
	
	// Create the screen sprite from the screen texture's internal texture.
	// The correct size of the sprite should be set by the texture.
	
	screenSprite.reset(new sf::Sprite(screenTexture->getTexture()));
	
	// Initialize the Console
	
	console->init(screenSize);
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
		if (activeScreen)
			activeScreen->preCheckEvents();
		
		Event event;
		
		while (window->pollEvent(event))
		{
			bool caught = checkGlobalEvent(event);
			
			if (!caught && consoleEnabled)
				caught = console->checkEvent(event);
			
			// Let the current state process the event
			
			if (!caught && activeScreen)
				caught = activeScreen->checkEvent(event);
		}
		
		// Advance the console's frame
		
		if (consoleEnabled)
			console->advanceFrame(deltaTime);
		
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
	screenTexture->clear(Color::Black);
	
	// Render the active screen to the render window
	
	if (activeScreen)
		screenTexture->draw(*activeScreen);
	
	// Render the console to the render window
	
	if (consoleEnabled)
		screenTexture->draw(*console);
	
	// Draw the screen onto the window
	
	screenTexture->display();
	window->draw(*screenSprite);
	
	// Flip the window's double buffer
	
	window->display();
}


bool WindowManager::checkGlobalEvent(sf::Event &event)
{
	// Check if the close button was pressed
	
	if (event.type == Event::Closed)
	{
		// Close the window and stop the loop
	
		closeWindow();
	}
	
	// Check for global key presses
	
	else if (event.type == Event::KeyPressed)
	{
		Event::KeyEvent keyEvent = event.key;
		
		if (keyEvent.code == Keyboard::Escape)
		{
			// Close the window and stop the loop
			
			closeWindow();
		}
		
		else if (keyEvent.code == Keyboard::Tab)
		{
			// Toggle the console state
			
			consoleEnabled = !consoleEnabled;
		}
		
		else
			return false;
	}
	
	else
		return false;
	
	return true;
}