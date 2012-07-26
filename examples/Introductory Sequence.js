

function init()
{
	// ~Introductory Sequence
	
	// Load and display the map
	
	game.loadMap("introductory_map.json");
	game.view(10, 18);
	game.displayMap();
	
	// ~Awe-inspiring, mystical music begins to play...
	
	// Unlike sound effects, music is streamed from a file to avoid long
	// load times. Music loops indefinitely until it is stopped or another
	// song is played.
	
	var awe = new Music("music/awe_inspiring_music.ogg");
	music.play(awe);
	
	// ~the sound of a clock ticking echoes ominously...
	
	// Calling `new Sounds()` loads the entire sound file into the memory
	// before playing, so it's usually best to define these variables before
	// loading the map in order to avoid lag during gameplay.
	
	var ticks = new Sound("sfx/clock_ticking.ogg")l
	sound.play(ticks);
	
	// ~dialogue fades onto the screen:
	
	// The user must press the "action" key (defined in config.json) to
	// continue to the next line of dialogue.
	
	narrator.say("It's about time, Rutherford. It's about time.");
	narrator.say("Hydroelectric power... you know of it?");
	narrator.say("Managing the stream, tending it, drinking the pools freshly stagnant.");
	
	// ~Mystical music crossfades with heroic introductory music
	
	var heroic = new Music("music/heroic_introductory.ogg");
	
	// Only one song can play at a time, so the previous song should be faded
	// out with a defined number of seconds to make a nice transition.
	
	music.fadeOut(2.5);
	music.play(heroic);
	
	// ~our hero is illuminated in the bottom center of the screen
	
	// Post-processing effects will go here, and possibly at the beginning
	// of this init() function. However, my mind explodes whenever
	// I begin to think of implementing that kind of functionality, so
	// I'll leave visual effects out for now.
	
	// ~wearing glasses, but looking as dashing as a bitwise character can be
	
	// Upon loading the Map State, (after the Main Menu State is completed, for
	// example) the player data is automatically loaded from "player.json",
	// as if `var player = new Character("player.json")` is called before the
	// init() function is run.
	// However, the "player" character is special since he is controlled by the
	// user, etc.
	
	// ~the rest of the room is illuminated outwards from the hero
	// ~a beautiful woman appears
	
	// Again, this loads a file from the hard drive and should be called
	// before loading the map in order to avoid lag during gameplay.
	
	var woman = new Character("characters/woman.json");
	woman.place(10, 21);
	
	// ~a swimming pool
	
	// This will be loaded onto the map when game.loadMap() is called at
	// the beginning of this script. The player will be blocked from walking
	// into it by defining a set of "wall" tiles in the Tiled map editor.
	
	// ~in the top left hand corner, a computer
	
	// "Entities" aren't defined in the map, so you must load them from
	// the scripting environment and place them at a coordinate.
	
	var computer = new Entity("entities/computer_C64.json")
	computer.place(6, 25);
	
	// ~and right in front of it, scratching his head, is our actual hero.
	
	player.place(10, 14);
	
	// This is a little interesting. Previously I intended character
	// movement to be based on directions and number of tiles, such as
	// `woman.walk(DOWN, 6)` or `woman.walk(0, -6)`, but absolute coordinates
	// might be easier to script. If this is a better option, a pathfinder
	// algorithm must be implemented, and an error should be thrown if the
	// pathfinder cannot find a path or if the coordinates are on a wall.
	
	woman.walk(10, 15);
	
	woman.say("Oh thank God you're both here, I have no idea what could be---");
	player.say("Ma'am, let me ask you one question before you go on.");
	player.say("Is your computer plugged in?");
	woman.say("Oh my god!");
	
	// ~She runs to the computer
	
	// The dialog box closes after the action button is pressed, and the woman
	// will begin walking to the new destination.
	
	woman.walk(6, 24);
	
	// The dialog box then opens to resume dialogue.
	
	woman.say("I didn't even think that mattered! Thank-you-thank-you so much!");
	
	// ~At this point, all praises are clearly being given to your
	// ~comrade, and not you
	
	woman.say("I am clearly giving praises to your comrade, and not you.");
	
	// ~so you PLUG IN THE COMPUTER and BOOT IT UP, using the PICK UP
	// ~and ACTION mechanisms
	
	// [Belt's note: Is the user controlling the hero, or is the
	// player character automatically performing these actions? Dialogue
	// shouldn't (and probably couldn't) be going on during gameplay.
	// That would conflict with the small graphics
	// display, the key input manager, and the game state.]
	
	// ~The two of them continue to have dialogue
	
	woman.say("...");
	ergo.say("...");
	
	// ~and your name is mentioned at some point by your partner
	
	ergo.say("...Arty...")
	
	// ~The play screen dims and an overlay, smaller than the screen,
	// ~comes up that looks like a crappy computer screen
	
	// [The graphics display already looks like a crappy computer screen. :) ]
	
	// Introducing GUI elements:
	// For now, I'll wait on further development of necessary components before
	// diving into GUI's. It's more of an advanced topic, so I'll leave it
	// for later.
	
	// A character must be loaded before anyone can say anything.
	
	var unknown1 = new Character("characters/unknown1.json");
	var unknown2 = new Character("characters/unknown2.json");
	var unknown3 = new Character("characters/unknown3.json");
	
	// ~(All three simultaneously)
	
	// Only one dialog box may be displayed at a time, but video game designers
	// tend to emulate this by displaying short lines of dialogue. Like so...
	
	unknown1.say("EEEEK!!");
	unknown2.say("Well, there it is.");
}
