/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "Entity.h"

using namespace bit;
using namespace sf;


Entity::Entity()
{
}


void Entity::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(*sprite, states);
}


void Entity::setTexture(shared_ptr<sf::Texture> texture)
{
	sprite.reset(new Sprite(*texture));
}
