//
//  Game.cpp
//  1942
//
//  Created by Nikos Xenakis on 29/12/15.
//  Copyright © 2015 Nikos Xenakis. All rights reserved.
//

#include "Game.hpp"

unsigned long Game::_currTime = 0;
Game::Game(){
    
    //FPS init
    _fps_lasttime = SDL_GetTicks(); //the last recorded time.
    _fps_frames = 0; //frames passed since the last recorded fps.
    _fps_current = 0;
    _gameState =SINGLEPLAYER_MENU;
}

int Game::OnExecute(){

    if(OnInit() == false) {
        return -1;
    }
	//Game Loop
    while ( !isExit()    ){
		setGameTime();
        while (SDL_PollEvent(&e)){
            OnEvent(&e);
        }
        
        OnLoop();
        OnRender();
        fpsLoop();
		

    }
    OnCleanup();
    return 0;
}



SDL_Window * Game::getWindow(){
    return _window;
}

SDL_Renderer * Game::getRenderer(){
    return _renderer;
}

GameState Game::getState(){
    return _gameState;
}

bool Game::isExit(){
    if (_gameState==EXIT) {
        return true;
    }
    return false;
}

bool Game::isMainMenu(){
    if (_gameState==SINGLEPLAYER_MENU || _gameState==MULTIPLAYER_MENU) {
        return true;
    }
    return false;
}

void Game::fpsLoop(){
    _fps_frames++;
	
    if (_fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000)
    {
        _fps_lasttime = SDL_GetTicks();
        _fps_current = _fps_frames;
       // std::cout<<"FPS: "<<_fps_current<<std::endl;
        _fps_frames = 0;
    }
    _fps_sprite->changeString(std::to_string(_fps_current),450,24);
    
}

unsigned long Game::getGameTime(){
    return _currTime;
}

SDL_Window * Game::_window;
SDL_Renderer * Game::_renderer;
