/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_StateManager_h
#define BitRPG_StateManager_h

#include <SFML/System.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;


namespace bit
{
	class State;
	class SplashState;
	class MapState;
	
	class StateManager
	{
	public:
		StateManager();
		
		enum StateType
		{
			BLANKSTATE,
			SPLASHSTATE,
			MAPSTATE
		};
		
		void initAllStates(const sf::Vector2u size);
		void changeState(StateType stateType);
		
		shared_ptr<State> getCurrentState();
		shared_ptr<SplashState> getSplashState();
		shared_ptr<MapState> getMapState();
		
	private:
		StateType currentStateType;
		
		shared_ptr<SplashState> splashState;
		shared_ptr<MapState> mapState;
	};
}

#endif
