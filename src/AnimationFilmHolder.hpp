#ifndef AnimationFilmHolder_hpp
#define AnimationFilmHolder_hpp

#include "includes.h"
#include <fstream>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "AnimationFilm.hpp"
class AnimationFilmHolder{
private:
    typedef std::map<std::string, AnimationFilm*> Films;
    Films _films;
    //BitmapLoader _bitmaps;
    static AnimationFilmHolder*  _holder; //singleton
  
    AnimationFilmHolder (void);
    ~AnimationFilmHolder();
    void AddAnimationFilm(SDL_Texture* texture ,std::vector<SDL_Rect> boxes ,string id);
public:
    
    //static const AnimationFilmHolder& Get(void);
    static AnimationFilmHolder* Get (void){
        if (!_holder)
            _holder = new AnimationFilmHolder();
        return _holder;
    }
    
    void    Load (const std::string& cataloge, SDL_Renderer* _renderer);
    void    CleanUp(void);
    AnimationFilm* GetFilm(const std::string id) ;
};
#endif