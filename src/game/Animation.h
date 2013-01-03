/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_Animation_h
#define BitRPG_Animation_h

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	struct Animation
	{
		std::vector<shared_ptr<sf::Texture> > frames;
		int subFrames;
	};
}


#endif
