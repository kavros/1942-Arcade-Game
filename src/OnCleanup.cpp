#include "Game.hpp"

void Game::cleanUpHolders(){
    AnimatorHolder::cleanup();
    AnimationHolder::cleanUp();
    SpritesHolder::cleanUp();
    AnimationFilmHolder::CleanUp();
    SoundHolder::cleanUp();
    
    
    AnimatorHolder* ah = AnimatorHolder::getAnimatorHolder();
    AnimationHolder* ath = AnimationHolder::getAnimationHolder();
    SpritesHolder* sh = SpritesHolder::getSpritesHolder();
    AnimationFilmHolder* afh = AnimationFilmHolder::Get();
    //SoundHolder* soh= SoundHolder::getSoundHolder();
    
    DestructionManager::commit();
    ;
}

void Game::OnCleanup(){
	if (_controller != nullptr){
		SDL_GameControllerClose(_controller);
		_controller = nullptr;
	}

    cleanUpHolders();

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}