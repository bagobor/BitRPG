/*
 *  BitRPG
 *  https://github.com/AndrewBelt/BitRPG
 *
 */

#include "StateManager.h"
#include "SplashState.h"
#include "MapState.h"

using namespace bit;


StateManager::StateManager()
{
	splashState.reset(new SplashState);
	mapState.reset(new MapState);
	
	// Initialize the default state
	
	currentStateType = BLANKSTATE;
}


void StateManager::initAllStates(const sf::Vector2u size)
{
	splashState->init(size);
	mapState->init(size);
}


void StateManager::changeState(StateType stateType)
{
	currentStateType = stateType;
}


StatePtr StateManager::getCurrentState()
{
	switch (currentStateType)
	{
	case BLANKSTATE:
		return StatePtr();
	break;
	
	case SPLASHSTATE:
		return splashState;
	break;
	
	case MAPSTATE:
		return mapState;
	break;
	}
}


SplashStatePtr StateManager::getSplashState()
{
	return splashState;
}


MapStatePtr StateManager::getMapState()
{
	return mapState;
}
