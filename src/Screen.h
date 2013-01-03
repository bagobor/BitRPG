/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Screen_h
#define BitRPG_Screen_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class Screen : public sf::Drawable
	{
	public:
		/**	Initializes the screen with the size in pixels
		*/
		void init(const sf::Vector2u screenSize)
		{
			this->screenSize = screenSize;
		}
		
		/**	Called before events are checked
		*/
		virtual void preCheckEvents() {}
		
		/**	Handles an SFML input event caught from the current window
			
			@returns whether the event was caught
		*/
		virtual bool checkEvent(sf::Event &event)
		{
			return false;
		}
		
		/**	Advances the screen's state by one frame
			
			@param deltaTime The time to advance in seconds
		*/
		virtual void advanceFrame(float deltaTime) {}
		
	protected:
		sf::Vector2u screenSize;
	};
}


#endif
