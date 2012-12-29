/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "ContentManager.h"
#include "Exception.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace bit;
using namespace sf;
using namespace std;
using namespace boost::filesystem;


ContentManager::ContentManager()
{
	// TODO
	// Resource path should be generated by platform and working directory
	
	// On Mac OS X, the resource path should point to the Resources
	// directory inside the app bundle.
	
	resourcePath = current_path();
}


shared_ptr<sf::Image> ContentManager::loadImage(const string &filename)
{
	string filePath = getAbsoluteFilename(filename);
	
	// Create a new image
	
	shared_ptr<sf::Image> image(new Image);
	bool success = image->loadFromFile(filePath);
	
	if (!success)
		throw bit::Exception("Could not load file " + filename);
	
	return image;
}


std::vector<shared_ptr<sf::Texture> > ContentManager::loadTileset(
	const std::string &filename, sf::Vector2u tileSize,
	int margin, int spacing)
{
	// Load the image
	
	shared_ptr<sf::Image> image = loadImage(filename);
	sf::Vector2u imageSize = image->getSize();
	
	// Check the math of the tileset dimensions
	
	if ((imageSize.x + spacing - 2 * margin) % (spacing + tileSize.x) != 0)
		throw bit::Exception("Tileset '" + filename +
				"' does not have a valid width");
	
	if ((imageSize.y + spacing - 2 * margin) % (spacing + tileSize.y) != 0)
		throw bit::Exception("Tileset '" + filename +
				"' does not have a valid height");
	
	// Calculate the number of tiles across the tileset in each dimension
	
	sf::Vector2u tilesetSize;
	tilesetSize.x = (imageSize.x + spacing - 2 * margin) / (spacing + tileSize.x);
	tilesetSize.y = (imageSize.y + spacing - 2 * margin) / (spacing + tileSize.y);
	
	sf::Vector2i tileSignedSize(tileSize.x, tileSize.y);
	
	// Extract each tile from the image
	
	std::vector<shared_ptr<sf::Texture> > textures;
	
	for (int tileY = 0; tileY < tilesetSize.y; ++tileY)
	{
		// Calculate the y position of the tile
		
		sf::Vector2i tilePosition;
		tilePosition.y = margin + (tileSize.y + spacing) * tileY;
		
		for (int tileX = 0; tileX < tilesetSize.x; ++tileX)
		{
			// Calculate the x position of the tile
			
			tilePosition.x = margin + (tileSize.x + spacing) * tileX;
			sf::IntRect tileRect(tilePosition, tileSignedSize);
			
			// Create the texture from the image around the rectangle boundary
			
			shared_ptr<sf::Texture> texture(new sf::Texture);
			texture->loadFromImage(*image, tileRect);
			
			// Add it to the textures list
			
			textures.push_back(texture);
		}
	}
	
	return textures;
}


string ContentManager::loadText(const string &filename)
{
	string filePath = getAbsoluteFilename(filename);
	
	// Open file stream
	
	ifstream file;
	file.open(filePath.c_str());
	
	// Dump entire file into buffer
	
	stringstream buffer;
	buffer << file.rdbuf();
	
	return buffer.str();
}


shared_ptr<sf::Font> ContentManager::loadFont(const string &filename)
{
	string filePath = getAbsoluteFilename(filename);
	
	// Create the font
	
	shared_ptr<sf::Font> font(new Font);
	bool success = font->loadFromFile(filePath);
	
	if (!success)
		throw bit::Exception("Font " + filePath + " could not be loaded");
	
	return font;
}


shared_ptr<Music> ContentManager::loadMusic(const string &filename)
{
	string filePath = getAbsoluteFilename(filename);
	
	// Create the music
	
	shared_ptr<Music> music(new Music);
	bool success = music->openFromFile(filename);
	
	if (!success)
		throw bit::Exception("Music " + filePath + " could not be loaded");
	
	return music;
}


std::string ContentManager::getAbsoluteFilename(const string &filename)
{
	path relativePath(filename);
	
	// Convert the relative path to absolute
	
	path absolutePath = absolute(relativePath, resourcePath);
	
	// Check if the file exists
	
	if (!is_regular_file(absolutePath))
	{
		string message("File ");
		message.append(absolutePath.string());
		message.append(" does not exist");
		
		throw bit::Exception(message);
	}
	
	return absolutePath.string();
}