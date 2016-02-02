#include "AnimationHolder.h"

AnimationHolder* AnimationHolder::_holder = 0;//singleton

AnimationHolder::AnimationHolder(){
    
}

AnimationHolder::~AnimationHolder(){
    
}

AnimationHolder* AnimationHolder::getAnimationHolder(){
    if(!_holder){
        _holder = new AnimationHolder();
    }
    return _holder;
}

void AnimationHolder::cleanUp(void){
    _holder->~AnimationHolder();
    _holder = NULL;
}

void AnimationHolder::add(Animation* anim){
	
    AnimationHolder::getAnimationHolder()->_map[anim->getId()]=anim;
}

Animation* AnimationHolder::getAnimation(animid_t str){
	
	if (AnimationHolder::getAnimationHolder()->_map[str] == nullptr){
		cout << "Error: Animation is not in map with animations !" << endl;
	}
	return AnimationHolder::getAnimationHolder()->_map[str];
}


using namespace rapidjson;

void    AnimationHolder::Load (const std::string& cataloge){
    std::string line, text;
    static  std::string  dataFilePath;
    
   dataFilePath = SRC_PATH + string(cataloge);
    
    std::ifstream file(dataFilePath);
    
    if (!file.is_open()){
        cout << dataFilePath << endl;
        cout << "ERROR:file does not opened" << endl;
        assert(0);
    }
    
    while(std::getline(file, line))
    {
        text += line + "\n";
    }
    const char* data = text.c_str();
    
    
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    assert(document["Animations"].IsArray());
    //assert(document["Sprites"][1].IsObject());
    const Value& animations = document["Animations"];
    //read all Moving Animations
    const Value& mAnimations = animations[0]["MovingAnimations"];
    assert(mAnimations.IsArray());
    for (rapidjson::SizeType i = 0; i < mAnimations.Size(); i++){
        const Value& mAnimation = mAnimations[i];
        //id
        std::string id = mAnimation["id"].GetString();
        int dx = mAnimation["dx"].GetInt();
        int dy = mAnimation["dy"].GetInt();
        int delay = mAnimation["delay"].GetInt();
        bool cont = mAnimation["continuous"].GetBool();
        AnimationHolder::getAnimationHolder()->add(new MovingAnimation(dx, dy, delay, cont, id));
    }
    
    //read all Tick Animations
    const Value& tAnimations = animations[1]["TickAnimations"];
    assert(tAnimations.IsArray());
    for (rapidjson::SizeType i = 0; i < tAnimations.Size(); i++){
        const Value& tAnimation = tAnimations[i];
        //id
        std::string id = tAnimation["id"].GetString();
        int delay = tAnimation["delay"].GetInt();
        int repetitions = tAnimation["repetitions"].GetInt();

        AnimationHolder::getAnimationHolder()->add(new TickAnimation(id ,delay ,repetitions) );

	
    }

    LoadMovingPathAnim(cataloge,2);
    
    
}

void    AnimationHolder::LoadMovingPathAnim (const std::string& cataloge,int n){
    
    std::string line, text;
    static  std::string  dataFilePath;
    
    dataFilePath = SRC_PATH + string(cataloge);
    
    std::ifstream file(dataFilePath);
    
    if (!file.is_open()){
        cout << dataFilePath << endl;
        cout << "ERROR:file does not opened" << endl;
        assert(0);
    }
    
    while(std::getline(file, line))
    {
        text += line + "\n";
    }
    const char* data = text.c_str();
    
    
    Document document;
    document.Parse(data);
    assert(document.IsObject());
    assert(document["Animations"].IsArray());
    //assert(document["Sprites"][1].IsObject());
    const Value& animations = document["Animations"];
    //read all Moving Path Animations
    const Value& mPathAnimations = animations[n]["MovingPathAnimations"];
    assert(mPathAnimations.IsArray());
    
    for (rapidjson::SizeType i = 0; i < mPathAnimations.Size(); i++)
    {
        std::list<PathEntry> _paths;
        const Value& mPathAnimation = mPathAnimations[i];
        const Value& paths = mPathAnimations[i]["paths"];
        assert(paths.IsArray());
        //id
        std::string id = mPathAnimation["id"].GetString();
        bool continuous = mPathAnimation["continuous"].GetBool();
        //bool doWhile = mPathAnimation["doWhile"].GetBool();
        for(rapidjson::SizeType j = 0; j < paths.Size(); j++){
            
            PathEntry pe;
            const Value& path = paths[j];
            //dx
            pe._visibility = path["visibility"].GetBool();
            pe._dx = path["dx"].GetInt();
            pe._dy = path["dy"].GetInt();
            pe._frame = path["frameNo"].GetInt();
            pe._delay = path["delay"].GetInt();
            if(mPathAnimation.HasMember("doWhile")){
                if(mPathAnimation["doWhile"].GetBool()){
                    int maxX = mPathAnimation["maxX"].GetInt();
                    int maxY = mPathAnimation["maxY"].GetInt();
                    int x = pe._dx;
                    int y = pe._dy;
                    if(maxX > 0 ){
                        if (maxY > 0){
                            assert(x >= 0 && x <= maxX && y >= 0 && y <= maxY);
                            while (x < maxX || y <maxY){
                                x +=pe._dx;
                                y +=pe._dy;
                                _paths.push_back(pe);
                            }
                        }else{
                            assert(x >= 0 && x <= maxX && y <= 0 && y >= maxY);
                            while (x < maxX || y > maxY){
                                x +=pe._dx;
                                y +=pe._dy;
                                _paths.push_back(pe);
                            }
                        }
                    }else{
                        if (maxY > 0){
                            string id2 = mPathAnimation["id"].GetString();
                            assert(x <= 0 && x >= maxX && y >= 0 && y <= maxY);
                            while (x > maxX || y < maxY){
                                x +=pe._dx;
                                y +=pe._dy;
                                _paths.push_back(pe);
                            }
                        }else{
                            assert(x <= 0 && x >= maxX && y <= 0 && y >= maxY);
                            while (x > maxX || y > maxY){
                                x +=pe._dx;
                                y +=pe._dy;
                                _paths.push_back(pe);
                            }
                        }
                    }
                }
                
            }
            _paths.push_back(pe);
            
        }
        
        AnimationHolder::getAnimationHolder()->add(new MovingPathAnimation(_paths,id,continuous));
        //add Sprite 2 Sprite Holder
    }
}