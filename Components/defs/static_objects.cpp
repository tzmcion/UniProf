#include "../static_objects.h"

Static_objects::Static_objects(SDL_Renderer *r){
    ren = r;
}

Static_objects::~Static_objects(){

}

//public functions

void Static_objects::add_static_object(const char *path, int x_pos, int y_pos,int width, int height){
    surf = IMG_Load(path);
    if(!surf){
        std::cout<<"\n";
        Colors::YELLOW(" [Warning] ");
        Colors::RESET("");
        std::cout << "Path " << path << " does not exist or does not contain .png element \n";
        surf = IMG_Load("./Assets/rim.png");
    }
    txt = SDL_CreateTextureFromSurface(ren,surf);
    SDL_FreeSurface(surf);
    Objects new_object;
    new_object.rect.x = x_pos;
    new_object.rect.y = y_pos;
    new_object.rect.w = width;
    new_object.rect.h = height;
    new_object.texture = txt;
    objects.push_back(new_object);
}

void Static_objects::render(int stamina, int energy){
    SDL_Rect rect;
    rect.x = 170;
    rect.y = 580;
    rect.w = 360 * stamina/100;
    rect.h = 40;
    SDL_SetRenderDrawColor(ren,150,0,0,255);
    SDL_RenderFillRect(ren,&rect);
    rect.x = 170;
    rect.y = 640;
    rect.w = 360 * energy/100;
    rect.h = 40;
    SDL_SetRenderDrawColor(ren,0,200,0,255);
    SDL_RenderFillRect(ren,&rect);
    for(int x = 0; x < objects.size(); x++){
        SDL_RenderCopy(ren,objects[x].texture,NULL, &objects[x].rect);
    }
}

//private functions