#ifndef includes_h
#define includes_h

#define RESOURCES_PATH string("")
#define CONFIG_PATH RESOURCES_PATH + string("config\\")
#define IMG_PATH RESOURCES_PATH + string("images\\")
#define SOUNDS_PATH RESOURCES_PATH + string("sounds\\")
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define WIN_WIDTH 768
#define WIN_HEIGHT 768

#define LEFT_FIGHTER  "left.fighter"
#define RIGHT_FIGHTER "right.fighter"

#include <iostream>
#include <assert.h>
#include <list>
#include <map>
#include <vector>
#include <algorithm>    // std::for_each
#include <fstream>
#include <time.h>       /* time */

using namespace std;

#endif /* includes_h */
