/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_EntityType_h
#define BitRPG_EntityType_h

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class JSONValue;
	class ContentManager;
	
	class EntityType
	{
	public:
		struct Animation
		{
			std::vector<shared_ptr<sf::Texture> > frames;
			int subFrames;
		};
		
		void load(JSONValue &entityValue);
		shared_ptr<Animation> getAnimation(const std::string &animationName);
		
		shared_ptr<ContentManager> contentManager;
		sf::Vector2u offsetPixels;
		
	private:
		std::map<std::string, shared_ptr<Animation> > animations;
	};
}


#endif
