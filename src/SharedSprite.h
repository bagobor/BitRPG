/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_SharedSprite_h
#define BitRPG_SharedSprite_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	/**	An SFML Sprite which holds onto a shared pointer of its texture
		
		The functionality is similar to its Sprite superclass, except that
		it uses a boost::shared_ptr to store a second reference to the
		sf::Texture.
		This guarantees that the texture will always exist in the lifetime
		of the SharedSprite, and the sf::Texture will be deleted upon
		the destruction of the SharedSprite, if it is the last to use it.
	*/
	class SharedSprite : public sf::Sprite
	{
	public:
		SharedSprite() {}
		
		/**	Sets the texture of the SharedSprite appropriately
		*/
		SharedSprite(shared_ptr<sf::Texture> sharedTexture);
		
		/**	Sets both the sf::Sprite texture and the shared texture reference
		*/
		void setTexture(shared_ptr<sf::Texture> sharedTexture);
		
	private:
		shared_ptr<sf::Texture> sharedTexture;
	};
}

#endif
