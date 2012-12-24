/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Screen.h"
#include "Exception.h"

using namespace bit;


void Screen::init(const sf::Vector2u screenSize)
{
	// Create the screen texture
	
	screenTexture.reset(new sf::RenderTexture);
	screenTexture->create(screenSize.x, screenSize.y);
	
	// Create the screen sprite from the screen texture's internal texture.
	// The correct size of the sprite should be set by the texture.
	
	screenSprite.reset(new sf::Sprite(screenTexture->getTexture()));
}


void Screen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	screenTexture->clear(sf::Color::Black);
	
	// Render the screen texture
	
	render();
	screenTexture->display();
	
	// Draw the screen sprite onto the render window
	
	target.draw(*screenSprite, states);
}
