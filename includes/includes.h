#ifndef includes_h
#define includes_h

#define RESOURCES_PATH string("")
#define SDL2_PATH "../libs/SDL2-2.0.16/include/SDL.h"
#define SDL2_IMAGE_PATH "../libs/SDL2_image-2.0.5/include/SDL_image.h"
#define SDL2_MIXER_PATH "../libs/SDL2_mixer-2.0.4/include/SDL_mixer.h"

#define CONFIG_PATH RESOURCES_PATH + string("config\\")
#define IMG_PATH RESOURCES_PATH + string("images\\")
#define SOUNDS_PATH RESOURCES_PATH + string("sounds\\")
#include SDL2_PATH
#include SDL2_IMAGE_PATH
#include SDL2_MIXER_PATH

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
