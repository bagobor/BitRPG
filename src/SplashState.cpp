/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "SplashState.h"
#include "Exception.h"

#include <stdio.h>
#include <iostream>
#include <boost/thread/thread.hpp>

using namespace bit;
using namespace sf;


SplashState::SplashState()
{
	fadeIn = 0.0f;
	hold = 0.0f;
	fadeOut = 0.0f;
}


void SplashState::checkEvent(Event &event)
{
	if (event.type == Event::KeyPressed)
	{
		// End state if the Escape key is pressed
		
		if (event.key.code == Keyboard::Escape)
		{
			//endState();
		}
	}
}


void SplashState::advanceFrame(float deltaTime)
{
	fadeTime += deltaTime;
	float fadeValue = 0.0f;
	
	// Calculate the piecewise function of the fade animation
	
	//           hold
	//          ______
	//         /      \
	// fadeIn /        \ fadeOut
	//
	
	if (fadeTime < fadeIn)
	{
		fadeValue = fadeTime / fadeIn;
	}
	else if (fadeTime < fadeIn + hold)
	{
		fadeValue = 1.0f;
	}
	else if (fadeTime < fadeIn + hold + fadeOut)
	{
		fadeValue = (fadeIn + hold + fadeOut - fadeTime) / fadeOut;
	}
	else
	{
		// The splash state has finished
		
		// TODO Finished splash state
		printf("That's all folks!\n");
		exit(0);
		
		return;
	}
	
	// Just in case, clip the fadeValue to [0, 1]
	
	if (fadeValue < 0.0f)
		fadeValue = 0.0f;
	
	else if (fadeValue > 1.0f)
		fadeValue = 1.0f;
	
	// Set the color to the alpha value
	
	Uint8 brightness = (Uint8) 255 * fadeValue;
	
	fadeColor.r = brightness;
	fadeColor.g = brightness;
	fadeColor.b = brightness;
	splashSprite->setColor(fadeColor);
}


void SplashState::draw(RenderTarget &target, RenderStates states) const
{
	// Draw the splash sprite
	
	target.draw(*splashSprite, states);
}


void SplashState::setTexture(TexturePtr texture)
{
	// Create the splash texture
	
	splashTexture = texture; 
	
	// Create the splash sprite
	
	splashSprite.reset(new Sprite(*splashTexture));
}


void SplashState::setFadeTimes(float fadeIn, float hold, float fadeOut)
{
	// Validate parameters
	
	if (fadeIn < 0.0f || hold < 0.0f || fadeOut < 0.0f)
		throw bit::Exception("Fade times cannot be negative");
	
	this->fadeIn = fadeIn;
	this->hold = hold;
	this->fadeOut = fadeOut;
	
	// Initialize the fade state
	
	fadeTime = 0.0f;
	
	// Set the color to black, transparent
	
	fadeColor = Color::Black;
}
