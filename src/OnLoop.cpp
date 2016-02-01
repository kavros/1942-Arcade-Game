#include "Game.hpp"

void Game::OnLoop() {
    static int i = 0;
    static int loopsRemainingToDelete = 10000 ;
    
    switch (_gameState) {
        case SINGLEPLAYER_MENU:
            break;
        case MULTIPLAYER_MENU:
            break;
        case SINGLEPLAYER_GAME:{
            
            SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");
            //cout << superAce->getState()<<endl;
            
            if(superAce->getState() == IN_COLUSION ){
                setState(GAME_OVER);
                return;
            }
            if(i % 50000 ==0){
                AnimatorHolder::getAnimatorHolder()->updateAllGrayPlaneAnimations();
				AnimatorHolder::getAnimatorHolder()->updateAllGrayJetsAnimations();

            }
            
            //commit destruction
            //proxeiri ilipoiisi ala nikola'
            //DestructionManager::printDestructionManager();
            
            if(loopsRemainingToDelete == 0){
                DestructionManager::commit();
                loopsRemainingToDelete = 10000;
            }
            loopsRemainingToDelete--;
            
            //Move Background
            Background::Get()->moveBackground(0,+1);
            
            //collision checker
            CollisionChecker::Check();

            //check animators and sprites  for delete if is out of window
            AnimatorHolder::checkAnimatorsForDelete();
            SpritesHolder::checkSpritesForDelete();

            //progress animators
			AnimatorHolder::progress(getGameTime());
            
            break;
        }
        case MULTIPLAYER_GAME:
            cout<<"under construction\n";
            assert(0);
            break;
        case EXIT:
            break;
		case PAUSE_MENU:
			break;
        case GAME_OVER:
            gameOver();
            break;
        default:
            break;
    }
    
}

void Game::gameOver(){
    static bool firstTime = true;
    //assert(0);
    if( firstTime ){
        updateHighScoreJson("config.json");
        AnimatorHolder::pauseAnimators();
        
        SpriteStringHolder::getSpriteString("game")->setVisibility(true);
        SpriteStringHolder::getSpriteString("over")->setVisibility(true);
        
        SpriteStringHolder::getSpriteString("press")->setVisibility(true);
        SpriteStringHolder::getSpriteString("space")->setVisibility(true);
        SpriteStringHolder::getSpriteString("for")->setVisibility(true);
        SpriteStringHolder::getSpriteString("exit2")->setVisibility(true);
        
        SpriteStringHolder::getSpriteString("startingReadyLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("startingPlayerLogo")->setVisibility(false);
        SpriteStringHolder::getSpriteString("numberOne")->setVisibility(false);
        firstTime = false;
        
    }else{
        //exit();
        //   assert(0);
    }
}