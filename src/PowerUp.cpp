#include "PowerUp.hpp"

PowerUp::PowerUp(std::string id, PowerUpType _powerUpType, unsigned  _frameNo, SDL_Rect _dstRect,SDL_Point  _point,
                 bool _isVisible,SpriteType _type,AnimationFilm* _currFilm)
:Sprite(id, _frameNo, _dstRect, _point, _isVisible, _type, _currFilm){
    powerUpType = _powerUpType;
}

//get
PowerUpType PowerUp::getPowerUpType(){
    return powerUpType;
}

void PowerUp::activatePowerUp(Sprite* arg){
    SuperAce* superAce = (SuperAce*)SpritesHolder::getSprite(SUPER_ACE, "SuperAce");

    switch ( getPowerUpType() ){
        case QUAD_GUN:{
            superAce->setBulletFrame(4);
            break;
        }
        case ENEMY_CRASH:
        {
            SpriteList* sl = SpritesHolder::getSprites(ALIEN_SHIP);
            for (std::list<Sprite*>::iterator it=sl->begin(); it != sl->end(); ++it){
                
                if((*it)->getVisibility() && !(*it)->isOutOfWindow()){
                     (*it)->setVisibility(false);
                     (*it)->setState(IN_COLUSION);
                     AnimatorHolder::createExplosion( (*it)->getDstRect() );
                }
            }
            break;
        }
        case SIDE_FIGHTERS:{
            superAce->addSideFighters();
            break;
        }
        case EXTRA_LIFE:{
            //not ready
            SuperAce* sa = superAce;
            sa->setSuperAceLives(sa->getSuperAceLives() + 1);
            std::string _remainingLives = "";
            for(int i = 0; i < sa->getSuperAceLives() ; i++){
                _remainingLives += "L";
            }
        SpriteStringHolder::getSpriteString("remainingLives")->changeString(_remainingLives, +5/*WIN_WIDTH - loops*12 -5*/, WIN_HEIGHT -15);}
            break;
        case NO_ENEMY_BULLETS:{
            SpriteList* sl = SpritesHolder::getSprites(ALIEN_SHIP);
            SpriteList::const_iterator it = sl->begin();
            while ( it != sl->end() ){
                if(((EnemyFighter*)(*it))->getEnemyFighterType() != EnemyFighterType(BIG_GREEN) ||
                        ((EnemyFighter*)(*it))->getEnemyFighterType() != EnemyFighterType(BIG_GREY))
                    
                            ((EnemyFighter*)(*it))->setEnemyFireEnable(false);
                ++it;
            }
            break;
        }
        case EXTRA_LOOP:{
            SuperAce* sa = superAce;
            sa->setSuperAceLoops(sa->getSuperAceLoops() + 1);
            std::string _remainingLoops = "";
            for(int i = 0; i < sa->getSuperAceLoops() ; i++){
                _remainingLoops += "R";
            }
            SpriteStringHolder::getSpriteString("remainingLoops")->changeString(_remainingLoops, WIN_WIDTH - sa->getSuperAceLoops() *13, WIN_HEIGHT - 15);
            break;
        }
        case THOUSAND_POINTS:
            Game::setScore(Game::getScore()+ 1000);
            break;
    }
}
