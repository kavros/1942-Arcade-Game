//
//  Game.cpp
//  1942
//
//  Created by Nikos Xenakis on 29/12/15.
//  Copyright © 2015 Nikos Xenakis. All rights reserved.
//

#include "Game.hpp"

unsigned long Game::_currTime = 0;
int Game::_score = 0;
int Game::_highScore = 0;
SpriteString* Game::_scoreSprite =nullptr;
SpriteString* Game::_highScoreSprite = nullptr;
Game::Game(){
    
    //FPS init
    _fps_lasttime = SDL_GetTicks(); //the last recorded time.
    _fps_frames = 0; //frames passed since the last recorded fps.
    _fps_current = 0;
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
    return Game::_gameState;
}

void Game::setState(GameState gameState){
    Game::_gameState = gameState;
}

bool Game::isExit(){
    if (_gameState==EXIT) {
        return true;
    }
    return false;
}

int Game::getHighScore() {
    return _highScore;
}

void Game::setHighScore(int s){
    _highScore = s;
}

int Game::getScore() {
    return _score;
}

void Game::setScore(int s){
    _score = s;
    updateScoreSprite();
    if (_score > _highScore){
        setHighScore(_score);
        updateHighScoreSprite();
    }
}

SpriteString* Game::getScoreSprite(void) {
    return _scoreSprite;
}
SpriteString* Game::getHighScoreSprite(void) {
    return _highScoreSprite;
}

void Game::updateScoreSprite(){
    std::string score = std::to_string(_score);
    _scoreSprite->changeString(score,20, 30);
}

void Game::updateHighScoreSprite(){
    std::string highScore = std::to_string(_highScore);
    _highScoreSprite->changeString(highScore,WIN_WIDTH/2 - (int) (highScore.size()*6), 30);
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
    _fps_sprite->changeString(std::to_string(_fps_current),450,30);
    
}

unsigned long Game::getGameTime(){
    return _currTime;
}

SDL_Window * Game::_window;
SDL_Renderer * Game::_renderer;
GameState Game::_gameState =SINGLEPLAYER_MENU;
