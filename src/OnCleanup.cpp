#include "Game.hpp"

void Game::OnCleanup(){
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}