
# SFML library

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})


# V8 library

find_package(V8 REQUIRED)

include_directories(${V8_INCLUDE_DIR})


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
	
	ScriptException.cpp
	ScriptManager.cpp
	JSONValue.cpp
	ScriptObject.cpp
	ConsoleObject.cpp
	GameObject.cpp
	MapObject.cpp
	
	DisplayManager.cpp
	StateManager.cpp
	SplashState.cpp
	MapState.cpp
	MapManager.cpp
)


target_link_libraries(BitRPG
	${SFML_LIBRARIES}
	${V8_LIBRARIES}
	${Boost_LIBRARIES}
)
