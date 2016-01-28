#include "Game.hpp"

void Game::OnCleanup(){
	if (_controller != nullptr){
		SDL_GameControllerClose(_controller);
		_controller = nullptr;
	}

    AnimatorHolder::cleanup();
    AnimationHolder::cleanUp();
    SpritesHolder::cleanUp();
    AnimationFilmHolder::CleanUp();
    SoundHolder::cleanUp();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}