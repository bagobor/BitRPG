/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */


#include "Console.h"
#include <math.h>

using namespace bit;


Console::Console()
{
	colorScheme[0] = sf::Color(0x28, 0x18, 0xB1, 0xb0);
	colorScheme[1] = sf::Color(0x38, 0x2F, 0x85, 0xb0);
	colorScheme[2] = sf::Color(0x13, 0x08, 0x73, 0xb0);
	colorScheme[3] = sf::Color(0x5B, 0x4C, 0xD8, 0xb0);
	colorScheme[4] = sf::Color(0x7C, 0x71, 0xD8, 0xb0);
	
	commandText.setCharacterSize(16);
	
	timeFraction = 0.0f;
}


void Console::init(const sf::Vector2u screenSize)
{
	Screen::init(screenSize);
	
	// Initialize consoleBackground
	
	sf::Vector2f consoleBackgroundSize(screenSize.x * 0.90f, screenSize.y * 0.30f);
	consoleBackground.setSize(consoleBackgroundSize);
	consoleBackground.setPosition(screenSize.x * 0.05f, screenSize.y * 0.05f);
	
	consoleBackground.setFillColor(colorScheme[4]);
	consoleBackground.setOutlineColor(colorScheme[3]);
	consoleBackground.setOutlineThickness(2.0f);
	
	// Initialize commandText
	
	commandText.setPosition(screenSize.x * 0.10f, screenSize.y * 0.10f);
}


bool Console::checkEvent(sf::Event &event)
{
	// Check for a text event
	
	if (event.type == sf::Event::TextEntered)
	{
		sf::Event::TextEvent textEvent = event.text;
		
		// Append the character to the commandString
		
		commandString += textEvent.unicode;
	}
	
	else if (event.type == sf::Event::KeyPressed)
	{
		sf::Event::KeyEvent keyEvent = event.key;
		
		if (keyEvent.code == sf::Keyboard::Back)
		{
			// Remove the last character of the commandString
			
			if (commandString.length() > 0)
				commandString.erase(commandString.length() - 1, 1);
		}
		
		else if (keyEvent.code == sf::Keyboard::Return)
		{
			// Execute the command
			
			// TODO
			
			// Clear the commandString
			
			commandString.clear();
		}
		
		else
			return false;
	}
	
	else
		return false;
	
	return true;
}


void Console::advanceFrame(float deltaTime)
{
	// Advance the time fraction and update the cursor state
	
	timeFraction = fmodf(timeFraction + deltaTime, 1.0f);
	
	if (timeFraction < 0.5f)
		commandText.setString(commandString + "_");
	
	else
		commandText.setString(commandString);
}


void Console::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Draw each of the console elements onto the target
	
	target.draw(consoleBackground);
	target.draw(commandText);
}
