#include "AnimationFilmHolder.hpp"
#include <iostream>
#include <string>

AnimationFilmHolder *AnimationFilmHolder::_holder = 0;

AnimationFilmHolder::AnimationFilmHolder (void){}

AnimationFilmHolder::~AnimationFilmHolder(){ CleanUp(); }

using namespace rapidjson;

//TODO LOAD with Json library
void    AnimationFilmHolder::Load (const std::string& cataloge,SDL_Renderer* _renderer){
    std::string line, text;
	
	static  std::string  dataFilePath = SRC_PATH + string(cataloge);

	std::ifstream file(dataFilePath);
 
    while(std::getline(file, line))
    {
        text += line + "\n";
    }
    const char* data = text.c_str();
    
    
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    assert(document["Films"].IsArray());
    assert(document["Films"][1].IsObject());
    const Value& films = document["Films"];
    for (rapidjson::SizeType i = 0; i < films.Size(); i++)
    {
        const Value& film = films[i];
        //id
        std::string id = film["id"].GetString();
        //path
        std::string path = film["path"].GetString();
        std::string  image = IMG_PATH + path;
        
        
        std::cout<<image<<std::endl;
        
        SDL_Surface* b = IMG_Load(image.c_str());
        if(!b) {
            printf("IMG_Load: %s\n", IMG_GetError());
            // handle error
            assert(0);
        }
        
        SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, b);
        if (!texture) {
            fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
            assert(0);
        }
      
        //rects
        const Value& rects = film["rects"];

        int rectNo = rects.Size();
        std::cout<<"ID: "<<id<<std::endl<<"Path: "<<path<<std::endl<<"RectNo: "<<rectNo<<std::endl;
        
        assert(film.IsObject());
        assert(film["id"].IsString());
        assert(film["rects"].IsArray());
        
        vector<SDL_Rect> boxes;
        for (rapidjson::SizeType j = 0; j < rects.Size(); j++)
        {
            const Value& rect = rects[j];
            
            SDL_Rect sdl_rect;
            sdl_rect.x = rect[0].GetInt();
            sdl_rect.y = rect[1].GetInt();
            sdl_rect.w = rect[2].GetInt();
            sdl_rect.h = rect[3].GetInt();
            boxes.push_back(sdl_rect);
            assert(rect[1].IsInt());
            printf("Rect [%d,%d,%d,%d] \n",rect[0].GetInt(),rect[1].GetInt(),rect[2].GetInt(),rect[3].GetInt());
		}
        assert(texture != NULL);
        AddAnimationFilm(texture ,boxes ,id);
    }
    
}


void AnimationFilmHolder::AddAnimationFilm(SDL_Texture* texture ,vector<SDL_Rect> boxes ,string id){
    AnimationFilm* film = new AnimationFilm(texture,boxes,id);
	assert(film->getTexture() );
    _films.insert ( std::pair<std::string, AnimationFilm*>(id,film) );
	assert(_films[id]!= nullptr);

}

void AnimationFilmHolder::CleanUp(void){
    for(Films::iterator i =_films.begin(); i!= _films.end(); ++i)
        delete(i->second);
    _films.clear();
}

AnimationFilm* AnimationFilmHolder::GetFilm(const std::string id) {
    
    Films::const_iterator i = _films.find(id);
    
    return i != _films.end() ? i->second : ( AnimationFilm*) 0;
	//return _films[id];
}