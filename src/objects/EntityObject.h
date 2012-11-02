/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_EntityObject_h
#define BitRPG_EntityObject_h

#include "../ScriptObject.h"

#include <SFML/Graphics.hpp>
#include <v8.h>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class EntityObject : public ScriptObject
	{
	public:
		EntityObject();
		~EntityObject();
		
		v8::Local<v8::Object> createInstance();
		
		shared_ptr<sf::Sprite> sprite;
	};
}

#endif
