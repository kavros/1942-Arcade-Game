//
//  Game.cpp
//  1942
//
//  Created by Nikos Xenakis on 29/12/15.
//  Copyright © 2015 Nikos Xenakis. All rights reserved.
//

#include "../includes/Game.hpp"

Uint32 Game::_fps_lasttime = SDL_GetTicks(); //the last recorded time.
Uint32 Game::_fps_current = 0; //the last recorded time.
Uint32 Game::_fps_frames = 0; //frames passed since the last recorded fps.

std::list<unsigned> Game::_powerUpsOfStage;
SDL_Window * Game::_window = 0;
SDL_Renderer * Game::_renderer = 0;
SDL_Event Game::event;
SDL_Event Game::prevEvent;

GameState Game::_gameState = GameState::SINGLEPLAYER_MENU;

//Game Variables
//unsigned Game::_remaining_loops_num = 3;
float Game::_spriteSize = 1;
int Game::_highScore = 0;
int Game::_score = 0;
unsigned long Game::_currTime = 0;

unsigned int Game::_totalEnemies = 0;
unsigned int Game::_deadEnemies  = 0;
//controller
SDL_GameController* Game::_controller = nullptr;

int Game::OnExecute(){

    if(OnInit() == false) {
        return -1;
    }
	//Game Loop
    while ( !isExit()    ){
		setGameTime();

        while (SDL_PollEvent(&event))
            OnEvent();

        OnLoop();
        //fpsLoop();
        OnRender();

    }
    OnCleanup();
    return 0;
}

void Game::setGameTime(){
    _currTime = SDL_GetTicks();
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

/*int Game::getRemainingLoops(void){
    return Game::_remaining_loops_num;
}*/

/*void Game::setRemainingLoops(int loops){
    Game::_remaining_loops_num = loops;
}*/
unsigned int Game::getTotalEnemies(){
	return _totalEnemies;
}
unsigned int Game::getDeadEnemies(){
	return _deadEnemies;
}
void Game::setToDeadEnemiesOneMore(){
	++_deadEnemies;
}
void Game::increaceTotalEnemies(){
	_totalEnemies++;
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

float Game::getSpriteSize() {
    return _spriteSize;
}

void Game::setSpriteSize(float s){
    _spriteSize= s;
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

void Game::updateScoreSprite(){
    std::string score = std::to_string(_score);
     SpriteStringHolder::getSpriteString("score")->changeString(score,20, 30);
}

void Game::updateHighScoreSprite(){
    std::string highScore = std::to_string(_highScore);
    SpriteStringHolder::getSpriteString("highScore")->changeString(highScore,WIN_WIDTH/2 - (int) (highScore.size()*6), 30);
    
    //write _highScore to config json     "highScore": 140

}


bool Game::isMainMenu(){
    if (_gameState==SINGLEPLAYER_MENU || _gameState==MULTIPLAYER_MENU) {
        return true;
    }
    return false;
}

void Game::fpsLoop(){
    
    Game::_fps_frames++;
	
    if (_fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000)
    {
        _fps_lasttime = SDL_GetTicks();
        _fps_current = _fps_frames;
        _fps_frames = 0;
    }
    SpriteStringHolder::getSpriteString("fps")->changeString(std::to_string(_fps_current),WIN_WIDTH -62,30);
    
}

unsigned long Game::getGameTime(){
    return _currTime;
}

void Game::setNextPowerUpType(unsigned p){
    assert( p < 7);
    _powerUpsOfStage.push_back(p);
}

unsigned Game::getNextPowerUpType(){

    assert(!_powerUpsOfStage.empty());
    unsigned p = _powerUpsOfStage.front();
    _powerUpsOfStage.pop_front();
    return p;
}


