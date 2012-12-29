/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */


#include "EntityType.h"
#include "../JSONValue.h"
#include "../ContentManager.h"
#include "../Exception.h"

#include <vector>

using namespace bit;


void EntityType::load(JSONValue &entityValue)
{
	// Get image settings
	
	JSONValue imageValue = entityValue["image"];
	std::string imageFilename = imageValue["filename"].toString();
	
	int margin = imageValue["margin"].toInteger();
	int spacing = imageValue["spacing"].toInteger();
	
	sf::Vector2u tileSize;
	tileSize.x = imageValue["tilewidth"].toInteger();
	tileSize.y = imageValue["tileheight"].toInteger();
	
	offsetPixels.x = imageValue["offsetx"].toInteger();
	offsetPixels.y = imageValue["offsety"].toInteger();
	
	// Load the tileset
	
	std::vector<shared_ptr<sf::Texture> > tilesetTextures =
		contentManager->loadTileset(imageFilename, tileSize, margin, spacing);
	
	int tilesetLength = tilesetTextures.size();
	
	// Get the animations
	
	JSONValue animationsValue = entityValue["animations"];
	int animationsLength = animationsValue.arrayLength();
	
	for (int animationIndex = 0; animationIndex < animationsLength; ++animationIndex)
	{
		JSONValue animationValue = animationsValue[animationIndex];
		
		// Create a new Animation
		
		shared_ptr<Animation> animation(new Animation);
		animation->subFrames = animationValue["framecount"].toInteger();
		std::string animationName = animationValue["name"].toString();
		
		// Iterate through each frame
		
		JSONValue framesValue = animationValue["frames"];
		int framesLength = framesValue.arrayLength();
		
		for (int frameIndex = 0; frameIndex < framesLength; ++frameIndex)
		{
			// Get the frame texture
			
			int frameId = framesValue[frameIndex].toInteger();
			
			if (frameId < 0 || tilesetLength <= frameId)
				throw bit::Exception("Tileset index out of bounds");
			
			shared_ptr<sf::Texture> frameTexture = tilesetTextures[frameId];
			
			// Add the frame to the frames list
			
			animation->frames.push_back(frameTexture);
		}
		
		// Add the animation to the animations list
		
		std::pair<std::string, shared_ptr<Animation> > animationPair(
			animationName, animation);
		animations.insert(animationPair);
	}
}


shared_ptr<EntityType::Animation> EntityType::getAnimation(const std::string &animationName)
{
	std::map<std::string, shared_ptr<Animation> >::iterator animationIt =
		animations.find(animationName);
	
	if (animationIt == animations.end())
		throw bit::Exception("Animation '" + animationName +"' not found");
	
	return animationIt->second;
}
