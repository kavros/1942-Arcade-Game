#include "Game.hpp"

void Game::OnLoop() {
    
    static int loopsRemainingToDelete = 10000 ;
    
    switch (_gameState) {
        case SINGLEPLAYER_MENU:
            break;
        case MULTIPLAYER_MENU:
            break;
        case SINGLEPLAYER_GAME:{
            
            Sprite* superAce = (Sprite*)SpritesHolder::getSpritesHolder()->getSprite(SUPER_ACE, "SuperAce");
            //cout << superAce->getState()<<endl;
            if(superAce->getState() == IN_COLUSION ){
                setState(GAME_OVER);
                return;
            }
            //commit destruction
            //proxeiri ilipoiisi ala nikola
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

            //trigger animators and bullets
            AnimatorHolder::triggerAnimators();
            AnimatorHolder::triggerBullets();

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