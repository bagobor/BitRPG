/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_AudioObject_h
#define BitRPG_AudioObject_h

#include "../ScriptObject.h"
#include "../ContentManager.h"

#include <v8.h>
#include <SFML/Audio.hpp>
#include <boost/smart_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class ContentManager;
	
	class AudioObject : public ScriptObject
	{
	public:
		AudioObject();
		v8::Local<v8::Object> createInstance();
		
		// V8-to-C++ binding functions
		
		static v8::Handle<v8::Value> playMusic(const v8::Arguments &args);
		static v8::Handle<v8::Value> stopMusic(const v8::Arguments &args);
		
		void playMusic(const std::string &filename);
		void stopMusic();
		
		shared_ptr<ContentManager> contentManager;
		
	private:
		shared_ptr<sf::Music> currentMusic;
	};
}

#endif
