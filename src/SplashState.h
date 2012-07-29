/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_SplashState_h
#define BitRPG_SplashState_h

#include "BitRPG.h"
#include "State.h"
#include <SFML/Graphics.hpp>


namespace bit
{
	class SplashState : public State
	{
	public:
		SplashState();
		
		void checkEvent(sf::Event &event);
		void advanceFrame(float deltaTime);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		void setTexture(sf::TexturePtr texture);
		void setFadeTimes(float fadeIn, float hold, float fadeOut);
		
	private:
		sf::TexturePtr splashTexture;
		sf::SpritePtr splashSprite;
		
		float fadeIn;
		float hold;
		float fadeOut;
		
		float fadeTime;
		sf::Color fadeColor;
	};
}

#endif
