#include "Game.hpp"

void Game::OnLoop() {
    
    static int loopsRemainingToDelete = 10000 ;
    
    switch (_gameState) {
        case SINGLEPLAYER_MENU:
            break;
        case MULTIPLAYER_MENU:
            break;
        case SINGLEPLAYER_GAME:{
            
            //check animators
            AnimatorHolder::checkAnimatorsForDelete();
            
            //commit destruction
            //proxeiri ilipoiisi ala nikola
            //DestructionManager::printDestructionManager();
            if(loopsRemainingToDelete == 0){
                DestructionManager::commit();
                loopsRemainingToDelete = 100;
            }
            loopsRemainingToDelete--;
            
            
            //Move Background
            Background::Get()->moveBackground(0,+2);
            
            //collision checker

            
            //trigger animators
            AnimatorHolder::triggerAnimators();
            
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
        default:
            break;
    }
    
}