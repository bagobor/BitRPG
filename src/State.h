/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_State_h
#define BitRPG_State_h

#include <SFML/Graphics.hpp>


namespace bit
{
	class State : public sf::Drawable
	{
	public:
		/**
		 * Initializes the state with the size of the RenderWindow
		 */
		virtual void init(const sf::Vector2u size) {}
		
		/**
		 * Handles an SFML input event caught from the current window
		 */
		virtual void checkEvent(sf::Event &event) {}
		
		/**
		 * Advances the state in time by the given amount
		 *
		 * Most of the graphics processing such as moving around sprites,
		 * rendering to offscreen textures, and manipulating entity properties
		 * should be done in this method.
		 * However, long calculations for other tasks should be left to other
		 * threads to reduce the risk of lag.
		 *
		 * @param deltaTime The time to advance in seconds
		 */
		virtual void advanceFrame(float deltaTime) {}
		
		/**
		 * Draws the graphics of this state to a render target
		 */
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const =0;
	};
}

#endif
