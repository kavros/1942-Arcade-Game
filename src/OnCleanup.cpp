#include "Game.hpp"

void Game::OnCleanup(){
	if (_controller != nullptr){
		SDL_GameControllerClose(_controller);
		_controller = nullptr;
	}
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}