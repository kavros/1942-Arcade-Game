#include "Game.hpp"

void Game::OnEvent(SDL_Event* event) {
    static SDL_Event prevEvent  = *event;
    
    if (event->type == SDL_QUIT){
        setState(EXIT);
        prevEvent = *event;
        return ;
    }
    
    if(event->window.event == SDL_WINDOWEVENT_FOCUS_LOST){
        setState(PAUSE_MENU);
    }
    
    switch (getState()) {
        case SINGLEPLAYER_MENU:
            if (event->key.keysym.sym == SDLK_SPACE){
                setState(SINGLEPLAYER_GAME);
            }
            else if (event->key.keysym.sym == SDLK_DOWN){
                setState(MULTIPLAYER_MENU);
            }
            break;
        case MULTIPLAYER_MENU:
            if (event->key.keysym.sym == SDLK_SPACE){
                setState(MULTIPLAYER_GAME);
            }
            else if (event->key.keysym.sym == SDLK_UP){
                setState(SINGLEPLAYER_MENU);
            }
            break;
		case SINGLEPLAYER_GAME:
		{
            
			Sprite* superAce = (Sprite*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
            cout << superAce->getState()<<endl;
            if(superAce->getState() == IN_COLUSION ){
                assert(0);
            }
            
			MovingPathAnimator* superAceStartingAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceStartingAnimator");
            assert(superAceStartingAnimator);
            
            if (superAce->getState() == STARTING){
                superAceStartingAnimator->start(getGameTime());
            }
            
			//if starting animator running then don't start any animator
			//when starting animator is finished remove all letters
			if (superAceStartingAnimator->getState() == ANIMATOR_RUNNING){
				return;
			}else{
                
                SpriteStringHolder::getSpriteString("startingReadyLogo")->setVisibility(false);
                SpriteStringHolder::getSpriteString("startingPlayerLogo")->setVisibility(false);
                SpriteStringHolder::getSpriteString("numberOne")->setVisibility(false);

			}

			if (event->type == SDL_KEYDOWN || event->type == SDL_CONTROLLERBUTTONDOWN){

				assert(superAce);
                
				MovingPathAnimator* superAceAnimatorLeft =
					(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeft");

                MovingPathAnimator* superAceAnimatorLeftLeft =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeftLeft");
                
				MovingPathAnimator* superAceAnimatorRight =
					(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRight");

                MovingPathAnimator* superAceAnimatorRightRight =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRightRight");
                
				MovingPathAnimator* superAceAnimatorUp =
					(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorUp");

				MovingPathAnimator* superAceAnimatorDown =
					(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorDown");

				MovingPathAnimator* superAceAnimatorManeuever =
					(MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorManeuver");

				assert(superAce->getType() == SUPER_ACE);

				if (event->key.keysym.sym == SDLK_ESCAPE
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_START
                ) {
					//pause
                    setState(PAUSE_MENU);
				}
				else if (event->key.keysym.sym == SDLK_q){
					//quit?
				}
				else if (event->key.keysym.sym == SDLK_LEFT
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {

                    if(event->key.keysym.sym != prevEvent.key.keysym.sym)
                        superAceAnimatorLeft->start(getGameTime());
                    else
                        superAceAnimatorLeftLeft->start(getGameTime());
				}
				else if (event->key.keysym.sym == SDLK_RIGHT
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT){
                    
                    if(event->key.keysym.sym != prevEvent.key.keysym.sym)
                        superAceAnimatorRight->start(getGameTime());
                    else
                        superAceAnimatorRightRight->start(getGameTime());

				}
				else if (event->key.keysym.sym == SDLK_UP
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
                    
					superAceAnimatorUp->start(getGameTime());
				}
				else if (event->key.keysym.sym == SDLK_DOWN
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
                    
					superAceAnimatorDown->start(getGameTime());

				}
				else if (event->key.keysym.sym == SDLK_SPACE
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_A){

					if (superAceAnimatorManeuever->getState() == ANIMATOR_RUNNING){
                        return;
                    }
                    
                    ((SuperAce*)superAce)->fire();

                    prevEvent = *event;
					break;
				}
				else if (event->key.keysym.sym == SDLK_a
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_X){
                    
                    ((SuperAce*)superAce)->doManeuever();
                    
                }

			}
            prevEvent = *event;
			break;
		}
        case MULTIPLAYER_GAME:
            //dont work
            assert(0);
            break;
		case PAUSE_MENU:
            pauseManager(event);
			break;
        case EXIT:
            break;
        default:
            setState(EXIT);
            break;
    }
    
}

void Game::pauseManager(SDL_Event* event){
    static bool firstTime = true;
    
    if( firstTime ){
        AnimatorHolder::pauseAnimators();
        
        SpriteStringHolder::getSpriteString("pause")->setVisibility(true);
        SpriteStringHolder::getSpriteString("exit")->setVisibility(true);
        SpriteStringHolder::getSpriteString("currsorUp")->setVisibility(false);
        SpriteStringHolder::getSpriteString("currsorDown")->setVisibility(true);
        
        SpriteStringHolder::getSpriteString("startingReadyLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("startingPlayerLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("numberOne")->setVisibility(false);
        firstTime = false;
        
    }
    
    if ((event->type == SDL_KEYDOWN || event->type == SDL_CONTROLLERBUTTONDOWN)){
        
        //navigation
        if (event->key.keysym.sym == SDLK_UP || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
            if( SpriteStringHolder::getSpriteString("currsorDown")->getVisibility() == true ){
                SpriteStringHolder::getSpriteString("currsorUp")->setVisibility(true);
                SpriteStringHolder::getSpriteString("currsorDown")->setVisibility(false);
            }
            return;
        }
        if (event->key.keysym.sym == SDLK_DOWN || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
            if( SpriteStringHolder::getSpriteString("currsorUp")->getVisibility() == true ){
                SpriteStringHolder::getSpriteString("currsorUp")->setVisibility(false);
                SpriteStringHolder::getSpriteString("currsorDown")->setVisibility(true);
            }
            return;
        }
        
        //selection
        if(event->key.keysym.sym == SDLK_ESCAPE || event->cbutton.button == SDL_CONTROLLER_BUTTON_START){
            AnimatorHolder::wakeUpAnimators(getGameTime());
            setState(SINGLEPLAYER_GAME);
            
            SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
            SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
            SpriteStringHolder::getSpriteString("currsorUp")->setVisibility(false);
            SpriteStringHolder::getSpriteString("currsorDown")->setVisibility(false);
            
            firstTime = true;
        }
        else if (event->key.keysym.sym == SDLK_SPACE){
            if( SpriteStringHolder::getSpriteString("currsorDown")->getVisibility() == true ){
                AnimatorHolder::wakeUpAnimators(getGameTime());
                setState(SINGLEPLAYER_GAME);
            }
            else if( SpriteStringHolder::getSpriteString("currsorUp")->getVisibility() == true ){
                //kill the animators
                setState(EXIT);
            }
            
            SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
            SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
            SpriteStringHolder::getSpriteString("currsorUp")->setVisibility(false);
            SpriteStringHolder::getSpriteString("currsorDown")->setVisibility(false);
            
            firstTime = true;
        }
        
    }
}