/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Entity_h
#define BitRPG_Entity_h

#include "BitRPG.h"


namespace bit
{
	class Entity : public sf::Drawable
	{
	public:
		Entity();
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void setTexture(sf::TexturePtr texture);
		
		sf::Vector2i mapPostion;
		
		sf::SpritePtr sprite;
		
	private:
		sf::TexturePtr texture;
	};
}


#endif
