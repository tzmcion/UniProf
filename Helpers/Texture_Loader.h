#pragma once
#include "./All.h"

class Texture_Loader{
    public:
        static SDL_Texture* create_texture(SDL_Renderer *r,const char* path);
};

// class Font_Loader{
//     public:
        
// }