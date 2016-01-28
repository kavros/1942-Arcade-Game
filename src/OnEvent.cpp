#include "Game.hpp"

void Game::OnEvent(SDL_Event* event) {
    static SDL_Event prevEvent  = *event;
    
    if (event->type == SDL_QUIT){
        setState(EXIT);
        prevEvent = *event;
        return ;
    }
    
    switch (getState()) {
        case SINGLEPLAYER_MENU:
            if (event->type == SDL_MOUSEBUTTONDOWN){
                setState(SINGLEPLAYER_GAME);
            }
            else if (event->key.keysym.sym == SDLK_DOWN){
                setState(MULTIPLAYER_MENU);
            }
            //prevEvent = *event;
            break;
        case MULTIPLAYER_MENU:
            if (event->type == SDL_MOUSEBUTTONDOWN){
                setState(MULTIPLAYER_GAME);
            }
            else if (event->key.keysym.sym == SDLK_UP){
                setState(SINGLEPLAYER_MENU);
            }
            //prevEvent = *event;
            break;
		case SINGLEPLAYER_GAME:
		{
			Sprite* superAce = (Sprite*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
            assert(superAce);
            
			MovingPathAnimator* superAceStartingAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceStartingAnimator");
            assert(superAceStartingAnimator);
            
            if (superAce->getState() == STARTING){
                superAceStartingAnimator->start(getGameTime());
                superAce->setState(MANEUVER);
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
					|| event->cbutton.button == SDL_CONTROLLER_BUTTON_START) {
					setState(PAUSE_MENU);
					
					//pause
				}
				else if (event->key.keysym.sym == SDLK_q
					){
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
					if (_remaining_loops_num > 0){
						superAce->setState(MANEUVER);
						superAceAnimatorManeuever->start(getGameTime());
						_remaining_loops_num--;
                        std::string _remainingLoops = "";
                        for(int i = 0; i <  _remaining_loops_num ; i++){
                            _remainingLoops += "R";
                        }

                        if(_remaining_loops_num != 0){
                            SpriteStringHolder::getSpriteString("remainingLoops")->changeString(_remainingLoops,WIN_WIDTH - (_remaining_loops_num*12), WIN_HEIGHT - 12);
                        }else{
                            SpriteStringHolder::getSpriteString("remainingLoops")->getSpriteAlphaNum(0)->setVisibility(false);
                        }
                        if (_remaining_loops_num == 2){
                            SpriteStringHolder::getSpriteString("remainingLoops")->changeString(_remainingLoops,WIN_WIDTH - (_remaining_loops_num*12), WIN_HEIGHT - 12);
						}
						else if (_remaining_loops_num == 1){
							SpriteStringHolder::getSpriteString("remainingLoops")->changeString("R", WIN_WIDTH - 12, WIN_HEIGHT - 12);
						}
						else if (_remaining_loops_num == 0){
							SpriteStringHolder::getSpriteString("remainingLoops")->getSpriteAlphaNum(0)->setVisibility(false);
                        }
					}
					else if (_remaining_loops_num == 0){

						//there are no loops
					}
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
			if ((event->type == SDL_KEYDOWN || event->type == SDL_CONTROLLERBUTTONDOWN)
				&& (event->key.keysym.sym == SDLK_ESCAPE || event->cbutton.button == SDL_CONTROLLER_BUTTON_START)){
				
				AnimatorHolder::wakeUpAnimators(getGameTime());
                
                SpriteStringHolder::getSpriteString("pause")->setVisibility(false);

				setState(SINGLEPLAYER_GAME);
			}
			else{
                
				AnimatorHolder::pauseAnimators();

                SpriteStringHolder::getSpriteString("pause")->setVisibility(true);
                
			}
			break;
        case EXIT:
            _gameState=EXIT;
            break;
        default:
            _gameState=EXIT;
            break;
    }
    
}