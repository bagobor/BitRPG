/*
 *  BitRPG
 *  https://github.com/Vortico/BitRPG
 *
 */

#ifndef BitRPG_BitRPG_h
#define BitRPG_BitRPG_h

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>


namespace bit
{
	class Application;
	class ContentManager;
	class ScriptManager;
	class DisplayManager;
	class StateManager;
	class EventManager;
	class MapManager;
	class Entity;
	class JSONValue;
	class MapLayer;
	class MapTile;
	class ScriptObject;
	class ScriptClass;
	class State;
	class SplashState;
	class MapState;
	
	typedef boost::shared_ptr<Application> ApplicationPtr;
	typedef boost::shared_ptr<ContentManager> ContentManagerPtr;
	typedef boost::shared_ptr<ScriptManager> ScriptManagerPtr;
	typedef boost::shared_ptr<DisplayManager> DisplayManagerPtr;
	typedef boost::shared_ptr<StateManager> StateManagerPtr;
	typedef boost::shared_ptr<EventManager> EventManagerPtr;
	typedef boost::shared_ptr<MapManager> MapManagerPtr;
	typedef boost::shared_ptr<Entity> EntityPtr;
	typedef boost::shared_ptr<MapLayer> MapLayerPtr;
	typedef boost::shared_ptr<MapTile> MapTilePtr;
	typedef boost::shared_ptr<State> StatePtr;
	typedef boost::shared_ptr<SplashState> SplashStatePtr;
	typedef boost::shared_ptr<MapState> MapStatePtr;
}


namespace sf
{
	typedef boost::shared_ptr<sf::Image> ImagePtr;
	typedef boost::shared_ptr<sf::Texture> TexturePtr;
	typedef boost::shared_ptr<sf::Sprite> SpritePtr;
	typedef boost::shared_ptr<sf::Font> FontPtr;
	typedef boost::shared_ptr<sf::Text> TextPtr;
}

#endif
