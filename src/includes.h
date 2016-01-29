#ifndef includes_h
#define includes_h

#ifdef  _WIN32
#define SRC_PATH  string("C:\\Users\\Alexis\\Source\\Repos\\1942\\src\\")
#define IMG_PATH  string("C:\\Users\\Alexis\\Source\\Repos\\1942\\images\\")
#define  SOUNDS_PATH string("C:\\Users\\Alexis\\Source\\Repos\\1942\\sounds\\")
#define SLASH "\\" 
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_mixer.h>

#else
#define IMG_PATH string(getenv("HOME")) + string("/1942/1942/images/")
#define SRC_PATH string(getenv("HOME")) + string("/1942/1942/src/")
#define SOUNDS_PATH string(getenv("HOME")) + string("/1942/1942/sounds/")
#define SLASH "/"
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#endif

#define WIN_X 100
#define WIN_Y 100

#define WIN_WIDTH 512
#define WIN_HEIGHT 512

#define BACKGROUNG_WIDTH 223
#define BACKGROUNG_HEIGHT 7680


#include <iostream>
#include <assert.h>
#include <list>
#include <map>
#include <vector>
#include <algorithm>    // std::for_each
#include <fstream>

using namespace std;

#endif /* includes_h */
