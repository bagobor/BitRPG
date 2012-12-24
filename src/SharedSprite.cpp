/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */


#include "SharedSprite.h"

using namespace bit;


SharedSprite::SharedSprite(shared_ptr<sf::Texture> sharedTexture)
{
	setTexture(sharedTexture);
}


void SharedSprite::setTexture(shared_ptr<sf::Texture> sharedTexture)
{
	this->sharedTexture = sharedTexture;
	sf::Sprite::setTexture(*sharedTexture);
}
