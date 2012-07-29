
# SFML library

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
#link_directories(${SFML_LIBRARIES})


# V8 library

find_package(V8 REQUIRED)

include_directories(${V8_INCLUDE_DIR})
#link_directories(${V8_LIBRARIES})


# Boost library

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.49.0 COMPONENTS system filesystem thread REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})


# BitRPG executable

add_executable(BitRPG
	main.cpp
	BitRPG.h
	Exception.cpp
	Application.cpp
	ContentManager.cpp
	
	ScriptManager.cpp
	ScriptObject.cpp
#	ItemObject.cpp
	
	ConsoleObject.cpp
	ScriptException.cpp
	
	DisplayManager.cpp
	StateManager.cpp
	SplashState.cpp
#	Entity.cpp
#	GameObject.cpp
	JSONValue.cpp
#	MapLayer.cpp
	MapManager.cpp
)


target_link_libraries(BitRPG ${SFML_LIBRARIES})
target_link_libraries(BitRPG ${V8_LIBRARIES})
target_link_libraries(BitRPG ${Boost_LIBRARIES})
