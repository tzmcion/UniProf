#include "../Field.h"

Field::Field(SDL_Renderer *r, std::vector<std::string>paths, int width, int height){
    ren = r;
    for(int x = 0; x < paths.size(); x++){
        surf = IMG_Load(paths[x].c_str());
        textures.push_back(SDL_CreateTextureFromSurface(ren,surf));
    }
    rect.w = width;
    rect.h = height;
    SDL_FreeSurface(surf);
}

Field::~Field(){}

void Field::render_field(int id,int x,int y){
    rect.x = x;
    rect.y = y;
    if(id > 1){
        SDL_RenderCopy(ren,textures[0],NULL,&rect);
    }
    if(id < textures.size()){
        if(id != 4){
            SDL_RenderCopy(ren,textures[id],NULL,&rect);
        }
    }
}


//Define wall here



