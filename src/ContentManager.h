/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_ContentManager_h
#define BitRPG_ContentManager_h

#include "BitRPG.h"
#include <string>
#include <map>
#include <boost/filesystem.hpp>


namespace bit
{
	class ContentManager
	{
	public:
		ContentManager();
		
		/**
		 * Loads an SFML image from a file
		 */
		sf::ImagePtr loadImage(const std::string &filename);
		sf::TexturePtr loadTexture(const std::string &filename,
			const sf::IntRect &area=sf::IntRect());
		
		/**
		 * Loads a plaintext file
		 *
		 * This operation is intended to be used for scripts, config files, and
		 * any other needed plaintext files.
		 */
		std::string loadText(const std::string &filename);
		
	private:
		std::string getAbsoluteFilename(const std::string &filename);
		
		/**
		 * The root content directory used to resolve relative file paths
		 */
		boost::filesystem::path resourcePath;
		
		std::map<std::string, sf::ImagePtr> images;
	};
}


#endif
