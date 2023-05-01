#include "../Messenger.h"

Messenger::Messenger(SDL_Renderer *r, const char* font_path,const char* img_path, int font_size){
    TTF_Init();
    ren = r;
    font = TTF_OpenFont(font_path,20);
    color = {255,255,255};
    //Now let's load the background image
    surf = IMG_Load(img_path);
    bg = SDL_CreateTextureFromSurface(ren,surf);
    SDL_FreeSurface(surf);
}

Messenger::~Messenger(){}

void Messenger::write(std::string txt, int x, int y){
    surf = TTF_RenderText_Solid(font,txt.c_str(),color);
    message = SDL_CreateTextureFromSurface(ren,surf);
    rect.x = x;
    rect.y = y;
    rect.h = surf->h + 10;
    rect.w = surf->w + 20;
    SDL_RenderCopy(ren,bg,NULL,&rect);
    rect.x += 10;
    rect.y += rect.h/20;
    rect.w = surf->w;
    rect.h = surf->h;
    SDL_RenderCopy(ren,message,NULL,&rect);
    SDL_FreeSurface(surf);
}

void Messenger::write_blank(std::string txt, int x, int y){
    surf = TTF_RenderText_Solid(font,txt.c_str(),color);
    message = SDL_CreateTextureFromSurface(ren,surf);
    rect.x = x;
    rect.y = y;
    rect.h = surf->h;
    rect.w = surf->w;
    SDL_RenderCopy(ren,message,NULL,&rect);
    SDL_FreeSurface(surf);
}

void Messenger::write_box(std::string txt, int x, int y, int &w, int &h){
    surf = TTF_RenderText_Solid(font,txt.c_str(),color);
    message = SDL_CreateTextureFromSurface(ren,surf);
    SDL_SetRenderDrawColor(ren,0,0,0,100);
    rect.x = x;
    rect.y = y-5;
    rect.h = surf->h + 5;
    rect.w = surf->w + 20;
    w = surf->w + 20;
    h = surf->h + 5;
    SDL_RenderFillRect(ren,&rect);
    rect.x += 10;
    rect.y += rect.h/20;
    rect.w = surf->w;
    rect.h = surf->h;
    SDL_RenderCopy(ren,message,NULL,&rect);
    SDL_FreeSurface(surf);
}