/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#ifndef BitRPG_StateManager_h
#define BitRPG_StateManager_h

#include "BitRPG.h"

#include <boost/thread/mutex.hpp>


namespace bit
{
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
		
		StatePtr getCurrentState();
		SplashStatePtr getSplashState();
		MapStatePtr getMapState();
		
	private:
		StateType currentStateType;
		
		SplashStatePtr splashState;
		MapStatePtr mapState;
	};
}

#endif
