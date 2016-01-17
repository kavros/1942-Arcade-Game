#include "Game.hpp"


void Game::OnEvent(SDL_Event* event) {
    
    if (event->type == SDL_QUIT){
        _gameState=EXIT;
        return ;
    }
    
    switch (_gameState) {
        case SINGLEPLAYER_MENU:
            if (event->type == SDL_MOUSEBUTTONDOWN){
                _gameState=SINGLEPLAYER_GAME;
            }
            else if (event->key.keysym.sym == SDLK_DOWN){
                _gameState = MULTIPLAYER_MENU;
                printf("DOWN\n");
            }
            break;
        case MULTIPLAYER_MENU:
            if (event->type == SDL_MOUSEBUTTONDOWN){
                _gameState=MULTIPLAYER_GAME;
            }
            else if (event->key.keysym.sym == SDLK_UP){
                _gameState = SINGLEPLAYER_MENU;
                printf("UP\n");
            }
            break;
        case SINGLEPLAYER_GAME:
			
			if (event->type == SDL_KEYDOWN){
				Sprite* superAce = (Sprite*)SpritesHolder::getSpritesHolder()->getSprites(SUPER_ACE)->front();
				//MovingPathAnimator* superAceAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimator");
				
                MovingPathAnimator* superAceAnimatorLeft =
							(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeft");

				MovingPathAnimator* superAceAnimatorRight = 
							(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRight");

				MovingPathAnimator* superAceAnimatorUp = 
							(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorUp");

				MovingPathAnimator* superAceAnimatorDown = 
							(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorDown");


				assert(superAce->getType() == SUPER_ACE);
				switch (event->key.keysym.sym) {
                    case SDLK_ESCAPE:
                        //pause
                        break;
                    case SDLK_q:
                        //quit?
                        break;
                    case SDLK_LEFT:{


                        superAceAnimatorLeft->start(getGameTime());
                        break;
                    }
                    case SDLK_RIGHT:{

                        
						superAceAnimatorRight->start( getGameTime());
                        break;
                    }
                    case SDLK_UP:{

                        
						superAceAnimatorUp->start( getGameTime());
                        break;
                    }
                    case SDLK_DOWN:{

						superAceAnimatorDown->start(getGameTime());
                        break;
                    }
                    case SDLK_SPACE:{
                        ((SuperAce*)superAce)->fire();
                        break;
                    }
                }
            }
			break;
        case MULTIPLAYER_GAME:
            break;
        case EXIT:
            _gameState=EXIT;
            break;
        default:
            _gameState=EXIT;
            break;
    }
    
}