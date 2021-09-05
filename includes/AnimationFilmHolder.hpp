#ifndef AnimationFilmHolder_hpp
#define AnimationFilmHolder_hpp

#include "../includes/includes.h"
#include <fstream>
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/writer.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../includes/AnimationFilm.hpp"
class AnimationFilmHolder{
private:
    typedef std::map<std::string, AnimationFilm*> Films;
    Films _films;
    //BitmapLoader _bitmaps;
    static AnimationFilmHolder*  _holder; //singleton
  
    AnimationFilmHolder (void);
    ~AnimationFilmHolder();
public:
    void AddAnimationFilm(SDL_Texture* texture ,std::vector<SDL_Rect> boxes ,string id);

    //static const AnimationFilmHolder& Get(void);
    static AnimationFilmHolder* Get (void){
        if (!_holder)
            _holder = new AnimationFilmHolder();
        return _holder;
    }
    
    void    Load (const std::string& cataloge, SDL_Renderer* _renderer);
    static void    CleanUp(void);
    AnimationFilm* GetFilm(const std::string id) ;
};
#endif