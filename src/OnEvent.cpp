#include "Game.hpp"

#include "MovingPathAnimator.h"

void Game::singleplayerGameOnEvent(SDL_Event* event , SDL_Event prevEvent){

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
    assert(superAce);
    
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
            
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            if(event->key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorLeft->start(getGameTime());
            else
                superAceAnimatorLeftLeft->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorLeft =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorLeft");
                assert(rightSideFighterAnimatorLeft);
                rightSideFighterAnimatorLeft->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorLeft =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorLeft");
                assert(leftSideFighterAnimatorLeft);
                leftSideFighterAnimatorLeft->start(getGameTime());
            }
        }
        else if (event->key.keysym.sym == SDLK_RIGHT
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT){
            
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            if(event->key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorRight->start(getGameTime());
            else
                superAceAnimatorRightRight->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorRight =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorRight");
                rightSideFighterAnimatorRight->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorRight =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorRight");
                leftSideFighterAnimatorRight->start(getGameTime());
            }
        }
        else if (event->key.keysym.sym == SDLK_UP
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            superAceAnimatorUp->start(getGameTime());
        }
        else if (event->key.keysym.sym == SDLK_DOWN
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            superAceAnimatorDown->start(getGameTime());
            
        }
        else if (event->key.keysym.sym == SDLK_SPACE
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_A){
            
            if (superAceAnimatorManeuever->getState() == ANIMATOR_RUNNING){
                return;
            }
            
            ((SuperAce*)superAce)->fire();
            
            prevEvent = *event;
            return;
        }
        else if (event->key.keysym.sym == SDLK_a
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_X){
            
            ((SuperAce*)superAce)->doManeuever();
            
        }
        
    }
    prevEvent = *event;
}

void Game::multiplayerGameOnEvent(SDL_Event* event , SDL_Event prevEvent){

    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
    assert(superAce);
    
    SuperAce* superAce2 = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce2");
    assert(superAce2);
    
    assert(0);  //until here
    
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
            
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            if(event->key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorLeft->start(getGameTime());
            else
                superAceAnimatorLeftLeft->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorLeft =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorLeft");
                assert(rightSideFighterAnimatorLeft);
                rightSideFighterAnimatorLeft->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorLeft =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorLeft");
                assert(leftSideFighterAnimatorLeft);
                leftSideFighterAnimatorLeft->start(getGameTime());
            }
        }
        else if (event->key.keysym.sym == SDLK_RIGHT
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT){
            
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            if(event->key.keysym.sym != prevEvent.key.keysym.sym)
                superAceAnimatorRight->start(getGameTime());
            else
                superAceAnimatorRightRight->start(getGameTime());
            if(superAce->getAttached(RIGHT_FIGHTER)){
                MovingPathAnimator* rightSideFighterAnimatorRight =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("RightSideFighterAnimatorRight");
                rightSideFighterAnimatorRight->start(getGameTime());
            }
            if(superAce->getAttached(LEFT_FIGHTER)){
                MovingPathAnimator* leftSideFighterAnimatorRight =
                (MovingPathAnimator*)AnimatorHolder::getAnimator("LeftSideFighterAnimatorRight");
                leftSideFighterAnimatorRight->start(getGameTime());
            }
        }
        else if (event->key.keysym.sym == SDLK_UP
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            superAceAnimatorUp->start(getGameTime());
        }
        else if (event->key.keysym.sym == SDLK_DOWN
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
            //AnimatorHolder::getAnimatorHolder()->UpdateAllGrayPlaneAnimations();
            superAceAnimatorDown->start(getGameTime());
            
        }
        else if (event->key.keysym.sym == SDLK_SPACE
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_A){
            
            if (superAceAnimatorManeuever->getState() == ANIMATOR_RUNNING){
                return;
            }
            
            ((SuperAce*)superAce)->fire();
            
            prevEvent = *event;
            return;
        }
        else if (event->key.keysym.sym == SDLK_a
                 || event->cbutton.button == SDL_CONTROLLER_BUTTON_X){
            
            ((SuperAce*)superAce)->doManeuever();
            
        }
        
    }
    prevEvent = *event;
}

void Game::OnEvent(SDL_Event* event) {
    static SDL_Event prevEvent  = *event;

    if (event->type == SDL_QUIT){
        setState(EXIT);
        return ;
    }
    
    if(event->window.event == SDL_WINDOWEVENT_FOCUS_LOST){
        setState(PAUSE_MENU);
    }
    
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
    assert(superAce);
    
    if(superAce->getState() == IN_COLUSION ){
        setState(GAME_OVER);
    }
    
    
    switch (getState()) {
        case SINGLEPLAYER_MENU:{
            if (event->key.keysym.sym == SDLK_SPACE){
                setState(SINGLEPLAYER_GAME);
            }
            else if (event->key.keysym.sym == SDLK_DOWN){
                setState(MULTIPLAYER_MENU);
            }
            break;
        }
        case MULTIPLAYER_MENU:{
            if (event->key.keysym.sym == SDLK_SPACE){
                setState(MULTIPLAYER_GAME);
            }
            else if (event->key.keysym.sym == SDLK_UP){
                setState(SINGLEPLAYER_MENU);
            }
            break;
        }
        case SINGLEPLAYER_GAME:{
            singleplayerGameOnEvent(event,prevEvent);
            break;
        }
        case MULTIPLAYER_GAME:{
            multiplayerGameOnEvent(event,prevEvent);
            break;
        }
        case GAME_OVER:{
            if (event->key.keysym.sym == SDLK_RETURN){
                setState(EXIT);
            }
            break;
        }
        case PAUSE_MENU:{
            pauseManager(event);
            break;
        }
        case END_OF_STAGE:{
            AnimatorHolder::pauseAnimators();
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
    
void Game::pauseManager(SDL_Event* event){
    static bool firstTime = true;
    Sprite* s = SpritesHolder::getSprite(GAME_INFO , "spriteInfoPlane");
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
    
    if ((event->type == SDL_KEYDOWN || event->type == SDL_CONTROLLERBUTTONDOWN)){
        
        //navigation
        if (event->key.keysym.sym == SDLK_UP || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP){
            if( s->getDstRect().y == down_y ){
                s->setDstRectY( up_y );
            }
            return;
        }
        if (event->key.keysym.sym == SDLK_DOWN || event->cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN){
            if( s->getDstRect().y == up_y ){
                s->setDstRectY( down_y );
            }
            return;
        }
        
        //selection
        if(event->key.keysym.sym == SDLK_ESCAPE || event->cbutton.button == SDL_CONTROLLER_BUTTON_START){
            AnimatorHolder::wakeUpAnimators(getGameTime());
            setState(SINGLEPLAYER_GAME);
            
            SpriteStringHolder::getSpriteString("pause")->setVisibility(false);
            SpriteStringHolder::getSpriteString("exit")->setVisibility(false);
            s->setVisibility(false);
  
            firstTime = true;
        }
        else if (event->key.keysym.sym == SDLK_SPACE){
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