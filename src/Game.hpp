//
//  Game.hpp
//  1942
//
//  Created by Nikos Xenakis on 29/12/15.
//  Copyright © 2015 Nikos Xenakis. All rights reserved.
//


#ifndef Game_hpp
#define Game_hpp
#define FRAME_VALUES 10


#include "includes.h"
//holders
#include "AnimationFilmHolder.hpp"
#include "AnimationHolder.h"
#include "SpritesHolder.hpp"

//sprites
#include "SpriteAlphaNum.hpp"
#include "SpriteString.hpp"
#include "SuperAce.h"
#include "Background.hpp"

//Animators
#include "MovingAnimator.h"
#include "AnimatorHolder.h"
#include "MovingPathAnimator.h"


enum GameState {
	SINGLEPLAYER_MENU,
	MULTIPLAYER_MENU,
    SINGLEPLAYER_GAME,
    MULTIPLAYER_GAME,
	EXIT
};

class Game{
    
private:
	/*************************************************************/
				//FRAME RATE VARIABLES//
	// How many frames time values to keep
	// The higher the value the smoother the result is...
	// Don't make it 0 or less :)
    
    #define FPS_INTERVAL 1.0 //seconds.
    
    Uint32 _fps_lasttime = SDL_GetTicks(); //the last recorded time.
    Uint32 _fps_current; //the current FPS.
    Uint32 _fps_frames = 0; //frames passed since the last recorded fps.
	
	/**************************************************************/

    static SDL_Window * _window;
    static SDL_Renderer * _renderer;
    
	SDL_Event e;

    GameState _gameState;

	//usefull for animation 
	static unsigned long _currTime ;
	void setGameTime(){ _currTime = SDL_GetTicks(); }
    SpriteString* _fps_sprite;

public:
    Game();
    
    //fps
    void fpsLoop();
    
    //<akatsarakis>
    int OnExecute();
    
    bool OnInit();
    
    void OnEvent(SDL_Event* e);
    
    void OnLoop();
    
    void OnRender();
    
    void OnCleanup();

    
    bool InitWindow();
    bool InitRenderer();
    bool InitData();

    bool InitMainMenuSinglePlayer();
    bool InitMainMenuMultiPlayer();
    bool InitBackground();
    bool InitSuperAce();
    bool InitGameInfo();
    void InitTestAnimator();

    //</akatsarakis>
    
    //get
    static SDL_Window * getWindow();
    static SDL_Renderer * getRenderer();
    SDL_Surface * getSurface();
    SDL_Texture * getTexture();
    GameState getState();
    static unsigned long getGameTime();
    
    //set
    
    //boolean
    bool isExit();
    bool isMainMenu();

	//fps functions
	void fpsThink();
	void fpsInit();

};

#endif /* Game_hpp */