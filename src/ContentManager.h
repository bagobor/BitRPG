/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ContentManager_h
#define BitRPG_ContentManager_h

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager
	{
	public:
		ContentManager();
		
		/**	Loads an SFML image from a file
		*/
		shared_ptr<sf::Image> loadImage(const std::string &filename);
		
		/**	Loads a list of textures from an image file
		*/
		std::vector<shared_ptr<sf::Texture> > loadTileset(
			const std::string &filename, sf::Vector2u tileSize,
			int margin=0, int spacing=0);
		
		/**	Loads a plaintext file
			
			This operation is intended to be used for scripts, config files, and
			any other plaintext files.
		*/
		std::string loadText(const std::string &filename);
		
		/**	Loads a font from a file
		*/
		shared_ptr<sf::Font> loadFont(const std::string &filename);
		
		/**	Loads a music file
		*/
		shared_ptr<sf::Music> loadMusic(const std::string &filename);
		
	private:
		std::string getAbsoluteFilename(const std::string &filename);
		
		/**	The root content directory used to resolve relative file paths
		*/
		boost::filesystem::path resourcePath;
	};
}


#endif
