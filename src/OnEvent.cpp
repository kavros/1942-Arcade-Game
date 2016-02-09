#include "Game.hpp"

#include "MovingPathAnimator.h"

void Game::singleplayerGameOnEvent(){
	
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce0");
    assert(superAce);

    if(!AnimatorHolder::movingEnable || AnimatorHolder::onManuevuer()){
        //can't move during start or end or onManuevuer
        return;
    }
    
	if (event.type == SDL_KEYDOWN || event.type == SDL_CONTROLLERBUTTONDOWN){
		static int i = 1;

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
        
        if (event.key.keysym.sym == SDLK_ESCAPE  ) {
            //pause
            setState(PAUSE_MENU);
        }
        else if (Game::event.key.keysym.sym == SDLK_q){
            //quit?
        }
        else if (event.key.keysym.sym == SDLK_LEFT ) {
            
            if(event.key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorLeft->start(getGameTime());
            else
                superAceAnimatorLeftLeft->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorLeft =(MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorLeft");
                if(rightSideFighterAnimatorLeft)
                    rightSideFighterAnimatorLeft->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorLeft =(MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorLeft");
                if(leftSideFighterAnimatorLeft)
                    leftSideFighterAnimatorLeft->start(getGameTime());
            }
        }
        else if (event.key.keysym.sym == SDLK_RIGHT ){
            
            if(event.key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorRight->start(getGameTime());
            else
                superAceAnimatorRightRight->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorRight =(MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorRight");
                if(rightSideFighterAnimatorRight)
                    rightSideFighterAnimatorRight->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorRight = (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorRight");
                if(leftSideFighterAnimatorRight)
                    leftSideFighterAnimatorRight->start(getGameTime());
            }
        }
        else if (event.key.keysym.sym == SDLK_UP ){
            superAceAnimatorUp->start(getGameTime());
        }
        else if (event.key.keysym.sym == SDLK_DOWN ){
            superAceAnimatorDown->start(getGameTime());
            
        }
        else if (event.key.keysym.sym == SDLK_SPACE ){

            superAce->fire();
            
            prevEvent = event;
        }
        else if (event.key.keysym.sym == SDLK_a ){
			
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
    static SDL_Event prev_event2;
    
    SuperAce* superAce2 = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce1");
	
	if (superAce2){
		superAce2->setVisibility(true);
	}
    if(!AnimatorHolder::movingEnable || !superAce2 ){
        //can't move during start or end
        return;
    }
    
    if ( event.type == SDL_CONTROLLERBUTTONDOWN){
        
        MovingPathAnimator* superAceAnimatorLeft = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeft1");
        assert(superAceAnimatorLeft);
        
        MovingPathAnimator* superAceAnimatorLeftLeft = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorLeftLeft1");
        assert(superAceAnimatorLeftLeft);
        
        MovingPathAnimator* superAceAnimatorRight = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRight1");
        assert(superAceAnimatorRight);
        
        MovingPathAnimator* superAceAnimatorRightRight = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorRightRight1");
        assert(superAceAnimatorRightRight);
        
        MovingPathAnimator* superAceAnimatorUp = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorUp1");
        assert(superAceAnimatorUp);
        
        MovingPathAnimator* superAceAnimatorDown = (MovingPathAnimator*)AnimatorHolder::getAnimator("SuperAceAnimatorDown1");
        assert(superAceAnimatorDown);
        
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
       
            superAceAnimatorLeft->start(getGameTime());

        }
		else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT){

            superAceAnimatorRight->start(getGameTime());
        }
		else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
            superAceAnimatorUp->start(getGameTime());
        }
		else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
            superAceAnimatorDown->start(getGameTime());
            
        }
		else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A){
            superAce2->fire();
            prevEvent = event;
        }
		else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X){
            
            superAce2->doManeuever();
        }
		else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B){
            if (!superAce2->isUndefeatable()){
                SoundHolder::playSound("i_will_never_die");
                superAce2->setUndefeatable(true);
                
            } else if(superAce2->isUndefeatable()){
                //sound for this case
                superAce2->setUndefeatable(false);
            }
            
        }
        
    }
    prev_event2 = event;
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
		SoundHolder::pauseSounds();

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
			SoundHolder::resumeSounds();
            setState(SINGLEPLAYER_GAME);

            SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
            SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
            s->setVisibility(false);
            
            firstTime = true;
        }
        else if (Game::event.key.keysym.sym == SDLK_RETURN){
            if( s->getDstRect().y == down_y ){
                AnimatorHolder::wakeUpAnimators(getGameTime());
				SoundHolder::resumeSounds();

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

void Game::singleplayerMenuOnEvent(){
    if (Game::event.key.keysym.sym == SDLK_RETURN){
        setState(SINGLEPLAYER_GAME);
    }
    else if (Game::event.key.keysym.sym == SDLK_DOWN){
        setState(MULTIPLAYER_MENU);
    }
}

void Game::multiplayerMenuOnEvent(){
    if (Game::event.key.keysym.sym == SDLK_RETURN){
        setState(MULTIPLAYER_GAME);
    }
    else if (Game::event.key.keysym.sym == SDLK_UP){
        setState(SINGLEPLAYER_MENU);
    }
}

void Game::OnEvent() {

    if (Game::event.type == SDL_QUIT){
        setState(EXIT);
        return ;
    }
    
    if(Game::event.window.event == SDL_WINDOWEVENT_FOCUS_LOST){
        //setState(PAUSE_MENU);
    }
    
    switch (getState()) {
        case SINGLEPLAYER_MENU:{
            singleplayerMenuOnEvent();
            break;
        }
        case MULTIPLAYER_MENU:{
            multiplayerMenuOnEvent();
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
        case EXIT:{
            break;
        }
        default:{
            setState(EXIT);
            break;
        }
    }
    
}
    
