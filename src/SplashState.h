/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_SplashState_h
#define BitRPG_SplashState_h

#include "State.h"
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class SplashState : public State
	{
	public:
		SplashState();
		
		void init(const sf::Vector2u size) {}
		void checkEvent(sf::Event &event);
		void advanceFrame(float deltaTime);
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		
		void setTexture(shared_ptr<sf::Texture> texture);
		void setFadeTimes(float fadeIn, float hold, float fadeOut);
		
	private:
		shared_ptr<sf::Texture> splashTexture;
		shared_ptr<sf::Sprite> splashSprite;
		
		float fadeIn;
		float hold;
		float fadeOut;
		
		float fadeTime;
		sf::Color fadeColor;
	};
}

#endif
