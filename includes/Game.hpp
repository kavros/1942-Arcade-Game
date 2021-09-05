

#ifndef Game_hpp
#define Game_hpp
#define FRAME_VALUES 10
#define FPS_INTERVAL 1.0 //seconds.

#include "../includes/includes.h"

//holders
#include "../includes/AnimationFilmHolder.hpp"
#include "../includes/AnimationHolder.h"
#include "../includes/SpritesHolder.hpp"
#include "../includes/CollisionChecker.hpp"
#include "../includes/SpriteStringHolder.hpp"
#include "../includes/SoundHolder.hpp"

//sprites
#include "../includes/SpriteAlphaNum.hpp"
#include "../includes/SuperAce.h"
#include "../includes/Background.hpp"
#include "../includes/PowerUp.hpp"

//Animators
#include "../includes/MovingAnimator.h"
#include "../includes/AnimatorHolder.h"
#include "../includes/MovingPathAnimator.h"


enum GameState {
	SINGLEPLAYER_MENU,
	MULTIPLAYER_MENU,
    SINGLEPLAYER_GAME,
    MULTIPLAYER_GAME,
	PAUSE_MENU,
	EXIT,
    GAME_OVER,
	END_OF_STAGE
};

class Game{
    
private:
    
    static Uint32 _fps_lasttime; //the last recorded time.
    static Uint32 _fps_current; //the current FPS.
    static Uint32 _fps_frames; //frames passed since the last recorded fps.
    
    static SDL_Window * _window;
    static SDL_Renderer * _renderer;
	static SDL_Event event;
    static SDL_Event prevEvent;

    static GameState _gameState;
    static std::list<unsigned> _powerUpsOfStage;
    //Game Variables
	static unsigned long _currTime ;
    static float _spriteSize;
    static int _highScore;
    static int _score;
	static unsigned int _totalEnemies;
	static unsigned int _deadEnemies;

	static bool _mute;
    //controller
	static SDL_GameController *_controller;

	
public:
    //basic functions
    
    //on init
    static bool OnInit();
    static bool InitWindow();
    static bool InitRenderer();
    static bool InitData();
    static void InitGame();
    static void InitGamePad();
    static bool InitGameInfo();
    static void LoadGameInfo (const std::string& cataloge);
    static int OnExecute();
    
    //on event
    static void OnEvent();
    static void singleplayerMenuOnEvent();
    static void multiplayerMenuOnEvent();
    static void singleplayerGameOnEvent();
    static void multiplayerGameOnEvent();
    static void pauseManager();
    static void gameOver();
    
    //on loop
    static void OnLoop();
    static void AIOnLoop();
    static void GameOnLoop();
    static void destructionManagerOnLoop();

    //on render
    static void OnRender();
    
    //on cleanup
    static void cleanUpHolders();
    static void OnCleanup();

    //get
    static SDL_Window * getWindow();
    static SDL_Renderer * getRenderer();
    static SDL_Surface * getSurface();
    static SDL_Texture * getTexture();
    static GameState getState();
    static unsigned long getGameTime();
    static int getHighScore(void)  ;
    static float getSpriteSize(void)  ;
    static int getScore(void)  ;
    static unsigned getNextPowerUpType();
	static unsigned int getTotalEnemies();
	static unsigned int getDeadEnemies();
    
    //updates
    static void updateHighScoreJson(const std::string& cataloge);
    static void updateHighScoreSprite();
    static void updateScoreSprite();
	static void UpdateAllGrayPlaneAnimations();

    //set
    static void setState(GameState gameState);
    static void setScore(int s);
    static void setSpriteSize(float s);
    static void setHighScore(int s);
    static void setNextPowerUpType(unsigned);
	static void setToDeadEnemiesOneMore();
	
    //boolean
    static bool isExit();
    static bool isMainMenu();

	//fps functions
    static void fpsLoop();
	static void fpsThink();
	static void fpsInit();

    //animation functions
    static void setGameTime();
	static void increaceTotalEnemies();
    
};


#endif /* Game_hpp */