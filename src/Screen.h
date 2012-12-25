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
		void init(const sf::Vector2u screenSize);
		
		/**	Handles an SFML input event caught from the current window
		*/
		virtual bool checkEvent(sf::Event &event);
		
		/**	Advances the screen's state by one frame
			
			@param deltaTime The time to advance in seconds
		*/
		virtual void advanceFrame(float deltaTime) {}
		
		/**	Draws the graphics of this state to a render target
		*/
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
	protected:
		shared_ptr<sf::RenderTexture> screenTexture;
		
		/**	Renders everything on the screen to the screenTexture
		*/
		virtual void render() const =0;
		
	private:
		shared_ptr<sf::Sprite> screenSprite;
	};
}


#endif
