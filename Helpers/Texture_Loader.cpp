#include "./Texture_Loader.h"

SDL_Texture* Texture_Loader::create_texture(SDL_Renderer *r,const char* path){
    SDL_Surface *surf;
    SDL_Texture *texture;
    surf = IMG_Load(path);
    if(surf){
        texture = SDL_CreateTextureFromSurface(r,surf);
    }
    SDL_FreeSurface(surf);
    return texture;
}