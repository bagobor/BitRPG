/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Entity_h
#define BitRPG_Entity_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class Entity : public sf::Drawable
	{
	public:
		Entity();
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void setTexture(shared_ptr<sf::Texture> texture);
		
		sf::Vector2i mapPostion;
		
		shared_ptr<sf::Sprite> sprite;
		
	private:
		shared_ptr<sf::Texture> texture;
	};
}


#endif
