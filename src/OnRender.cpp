#include "Game.hpp"

void Game::OnRender() {
    //Render the scene

    SDL_RenderClear(_renderer);
    
    //Draw the texture
    switch (_gameState) {
        case SINGLEPLAYER_MENU:
            SpritesHolder::getSpritesHolder()->displaySprites(_renderer,MAIN_MENU_SINGLEPLAYER);
            break;
        case MULTIPLAYER_MENU:
            SpritesHolder::getSpritesHolder()->displaySprites(_renderer,MAIN_MENU_MULTIPLAYER);
            break;
        case SINGLEPLAYER_GAME:

            SpritesHolder::getSpritesHolder()->displayGameSprites(_renderer);
            break;
        case MULTIPLAYER_GAME:
            cout<<"under construction\n";
            assert(0);
            break;
        case EXIT:
            cout<<"Exit\n";
            break;
		case PAUSE_MENU:
			SpritesHolder::getSpritesHolder()->displayGameSprites(_renderer);
			break;
        case GAME_OVER:
            SpritesHolder::getSpritesHolder()->displayGameSprites(_renderer);

            break;
		case END_OF_STAGE:
			SpritesHolder::getSpritesHolder()->displayGameSprites(_renderer);
			break;
        default:
            assert(0);
            break;
    }
    
    SDL_RenderPresent(_renderer);
    
    //Take a quick break after all that hard work
   // SDL_Delay(100);
}

