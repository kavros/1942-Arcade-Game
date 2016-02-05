#include "Game.hpp"

#include "MovingPathAnimator.h"

void Game::singleplayerGameOnEvent(){

	

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);
	
    MovingPathAnimator* superAceStartingAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceStartingAnimator0");
    assert(superAceStartingAnimator);
    
    //if starting animator running then don't start any animator
    //when starting animator is finished remove all letters
    if (superAceStartingAnimator->getState() == ANIMATOR_RUNNING){
        return;
    }else{
        
        SpriteStringHolder::getSpriteString("startingReadyLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("startingPlayerLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("numberOne")->setVisibility(false);
        
    }
    
	if (event.type == SDL_KEYDOWN || event.type == SDL_CONTROLLERBUTTONDOWN){

        MovingPathAnimator* superAceAnimatorLeft =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeft0");
        
        MovingPathAnimator* superAceAnimatorLeftLeft =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeftLeft0");
        
        MovingPathAnimator* superAceAnimatorRight =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRight0");
        
        MovingPathAnimator* superAceAnimatorRightRight =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRightRight0");
        
        MovingPathAnimator* superAceAnimatorUp =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorUp0");
        
        MovingPathAnimator* superAceAnimatorDown =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorDown0");
        
        if (event.key.keysym.sym == SDLK_ESCAPE || event.cbutton.button == SDL_CONTROLLER_BUTTON_START ) {
            //pause
            setState(PAUSE_MENU);
        }
        else if (Game::event.key.keysym.sym == SDLK_q){
            //quit?
        }
        else if (event.key.keysym.sym == SDLK_LEFT || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
            
            if(event.key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorLeft->start(getGameTime());
            else
                superAceAnimatorLeftLeft->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorLeft =(MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorLeft");
                assert(rightSideFighterAnimatorLeft);
                rightSideFighterAnimatorLeft->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorLeft =(MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorLeft");
                assert(leftSideFighterAnimatorLeft);
                leftSideFighterAnimatorLeft->start(getGameTime());
            }
        }
        else if (event.key.keysym.sym == SDLK_RIGHT || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT){
            
            if(event.key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorRight->start(getGameTime());
            else
                superAceAnimatorRightRight->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorRight =(MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorRight");
                assert(rightSideFighterAnimatorRight);
                rightSideFighterAnimatorRight->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorRight = (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorRight");
                assert(leftSideFighterAnimatorRight);
                leftSideFighterAnimatorRight->start(getGameTime());
            }
        }
        else if (event.key.keysym.sym == SDLK_UP || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
            superAceAnimatorUp->start(getGameTime());
        }
        else if (event.key.keysym.sym == SDLK_DOWN || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
            superAceAnimatorDown->start(getGameTime());
            
        }
        else if (event.key.keysym.sym == SDLK_SPACE || event.cbutton.button == SDL_CONTROLLER_BUTTON_A){

            superAce->fire();
            
            prevEvent = event;
        }
        else if (event.key.keysym.sym == SDLK_a || event.cbutton.button == SDL_CONTROLLER_BUTTON_X){
			
            superAce->doManeuever();
		}
		else if (event.key.keysym.sym == SDLK_c){
			if (!superAce->isUndefeatable()){
				SoundHolder::playSound("i_will_never_die");
                superAce->setUndefeatable(true);
              
			} else if(superAce->isUndefeatable()){
                //sound for this case
                superAce->setUndefeatable(false);

			}

		}
        
    }
    prevEvent = event;
}

void Game::multiplayerGameOnEvent(){
    
    SuperAce* superAce2 = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce1");
    if(!superAce2 || superAce2->getState() == IN_COLUSION)
        return;
    
    superAce2->setVisibility(true);
    
    MovingPathAnimator* superAce2StartingAnimator = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceStartingAnimator1");
    assert(superAce2StartingAnimator);
    
    
    if (superAce2->getState() == STARTING){
        superAce2StartingAnimator->start(getGameTime());
    }
    
    if (event.type == SDL_KEYDOWN || event.type == SDL_CONTROLLERBUTTONDOWN){
        
        MovingPathAnimator* superAce2AnimatorLeft =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeft1");
        
        MovingPathAnimator* superAce2AnimatorLeftLeft =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeftLeft1");
        
        MovingPathAnimator* superAce2AnimatorRight =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRight1");
        
        MovingPathAnimator* superAce2AnimatorRightRight =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRightRight1");
        
        MovingPathAnimator* superAce2AnimatorUp =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorUp1");
        
        MovingPathAnimator* superAce2AnimatorDown =
        (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorDown1");
        
        if (event.key.keysym.sym == SDLK_j/* || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT*/) {
            
            if(event.key.keysym.sym != prevEvent.key.keysym.sym)
                superAce2AnimatorLeft->start(getGameTime());
            else
                superAce2AnimatorLeftLeft->start(getGameTime());
            
            if(superAce2->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorLeft =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorLeft");
                assert(rightSideFighterAnimatorLeft);
                rightSideFighterAnimatorLeft->start(getGameTime());
            }
            if(superAce2->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorLeft =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorLeft");
                assert(leftSideFighterAnimatorLeft);
                leftSideFighterAnimatorLeft->start(getGameTime());
            }
            
        }
        else if (event.key.keysym.sym == SDLK_l/* || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT*/){
            
            if(event.key.keysym.sym != prevEvent.key.keysym.sym)
                superAce2AnimatorRight->start(getGameTime());
            else
                superAce2AnimatorRightRight->start(getGameTime());
            
            if(superAce2->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorRight =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorRight");
                rightSideFighterAnimatorRight->start(getGameTime());
            }
            if(superAce2->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorRight =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorRight");
                leftSideFighterAnimatorRight->start(getGameTime());
            }
            
        }
        else if (event.key.keysym.sym == SDLK_i/* || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP*/){
            superAce2AnimatorUp->start(getGameTime());
        }
        else if (event.key.keysym.sym == SDLK_k/* || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN*/){
            superAce2AnimatorDown->start(getGameTime());
            
        }
        else if (event.key.keysym.sym == SDLK_t/* || event.cbutton.button == SDL_CONTROLLER_BUTTON_A*/){
            
            superAce2->fire();
            
            prevEvent = event;
        }
        else if (event.key.keysym.sym == SDLK_y/* || event.cbutton.button == SDL_CONTROLLER_BUTTON_X*/){
            superAce2->doManeuever();
        }
        
    }
    prevEvent = event;
}

void Game::pauseManager(){
    static bool firstTime = true;
    Sprite* s = SpritesHolder::getSprite(GAME_INFO , "spriteInfoPlane0");
    assert(s);
    
    unsigned x = WIN_WIDTH / 2 -(5*6) - 20;
    s->setDstRectX( x );
    
    unsigned down_y = WIN_HEIGHT / 2 - 3;
    unsigned up_y = WIN_HEIGHT / 2 - 20;
    
    if( firstTime ){
        AnimatorHolder::pauseAnimators();
        
        SpriteStringHolder::getSpriteString("exit")->setVisibility(true);
        SpriteStringHolder::getSpriteString("pause")->setVisibility(true);
        
        /*down*/
        s->setDstRectY( down_y );
        s->setVisibility(true);
        
        SpriteStringHolder::getSpriteString("startingReadyLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("startingPlayerLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("numberOne")->setVisibility(false);
        firstTime = false;
        
    }
    
    if ((Game::event.type == SDL_KEYDOWN || Game::event.type == SDL_CONTROLLERBUTTONDOWN)){
        
        //navigation
        if (Game::event.key.keysym.sym == SDLK_UP || Game::event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
            if( s->getDstRect().y == down_y ){
                s->setDstRectY( up_y );
            }
            return;
        }
        if (Game::event.key.keysym.sym == SDLK_DOWN || Game::event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
            if( s->getDstRect().y == up_y ){
                s->setDstRectY( down_y );
            }
            return;
        }
        
        //selection
        if(Game::event.key.keysym.sym == SDLK_ESCAPE || Game::event.cbutton.button == SDL_CONTROLLER_BUTTON_START){
            AnimatorHolder::wakeUpAnimators(getGameTime());
            setState(SINGLEPLAYER_GAME);
            
            SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
            SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
            s->setVisibility(false);
            
            firstTime = true;
        }
        else if (Game::event.key.keysym.sym == SDLK_SPACE){
            if( s->getDstRect().y == down_y ){
                AnimatorHolder::wakeUpAnimators(getGameTime());
                setState(SINGLEPLAYER_GAME);
            }
            else if(  s->getDstRect().y == up_y ){
                //kill the animators
                setState(EXIT);
            }
            
            SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
            SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
            s->setVisibility(false);
            
            firstTime = true;
        }
        
    }
}

void Game::OnEvent() {

    if (Game::event.type == SDL_QUIT){
        setState(EXIT);
        return ;
    }
    
    if(Game::event.window.event == SDL_WINDOWEVENT_FOCUS_LOST){
        setState(PAUSE_MENU);
    }
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);
    
    if(superAce->getState() == IN_COLUSION ){
        setState(GAME_OVER);
    }
    
    
    switch (getState()) {
        case SINGLEPLAYER_MENU:{
            if (Game::event.key.keysym.sym == SDLK_SPACE){
                setState(SINGLEPLAYER_GAME);
            }
            else if (Game::event.key.keysym.sym == SDLK_DOWN){
                setState(MULTIPLAYER_MENU);
            }
            break;
        }
        case MULTIPLAYER_MENU:{
            if (Game::event.key.keysym.sym == SDLK_SPACE){
                setState(MULTIPLAYER_GAME);
            }
            else if (Game::event.key.keysym.sym == SDLK_UP){
                setState(SINGLEPLAYER_MENU);
            }
            break;
        }
        case SINGLEPLAYER_GAME:{
            singleplayerGameOnEvent();
            break;
        }
        case MULTIPLAYER_GAME:{
            singleplayerGameOnEvent();
            multiplayerGameOnEvent();
            break;
        }
        case GAME_OVER:{
            if (Game::event.key.keysym.sym == SDLK_RETURN){
                setState(EXIT);
            }
            break;
        }
        case PAUSE_MENU:{
            pauseManager();
            break;
        }
        case END_OF_STAGE:{
            AnimatorHolder::pauseAnimators();
            setState(GAME_OVER);
            break;
        }
        case EXIT:
            break;
        default:{
            setState(EXIT);
            break;
        }
    }
    
}
    
