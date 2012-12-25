/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Console_h
#define BitRPG_Console_h

#include "Screen.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;
using boost::scoped_ptr;


namespace bit
{
	class Console : public Screen
	{
	public:
		Console();
		
		/**	Initializes the screen with the size in pixels
		*/
		void init(const sf::Vector2u screenSize);
		
		/**	Handles an SFML input event caught from the current window
		*/
		bool checkEvent(sf::Event &event);
		
		/**	Advances the screen's state by one frame
			
			@param deltaTime The time to advance in seconds
		*/
		void advanceFrame(float deltaTime);
		
		/**	Draws the graphics of this state to a render target
		*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
	private:
		sf::RectangleShape consoleBackground;
		
		std::string commandString;
		sf::Text commandText;
		float timeFraction;
		
		sf::Color colorScheme[5];
	};
}

#endif
