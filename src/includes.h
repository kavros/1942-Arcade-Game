//
//  includes.h
//  1942
//
//  Created by Nikos Xenakis on 30/12/15.
//  Copyright © 2015 Nikos Xenakis. All rights reserved.
//
#ifndef includes_h
#define includes_h

#ifdef  _WIN32
#define SRC_PATH  string("C:/Users/αλεξης/Source/Repos/1942/src/")
#define IMG_PATH  string("C:/Users/αλεξης/Source/Repos/1942/images/")
#define SLASH "\\" 
#include <SDL_image.h>
#include <SDL.h>

#else
#define IMG_PATH string(getenv("HOME")) + string("/1942/1942/images/")
#define SRC_PATH string(getenv("HOME")) + string("/1942/1942/src/")
#define SLASH "/"
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
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

using namespace std;

#endif /* includes_h */
