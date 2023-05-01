#include "../Buttons.h"

Buttons::Buttons(SDL_Renderer *r){
    ren = r;
    surf = IMG_Load("./Assets/buttons/button1.png");
    cur1 = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    cur2 = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    Button but;
    but.txt = SDL_CreateTextureFromSurface(r,surf);
    SDL_FreeSurface(surf);
    but.rect.x = 500;
    but.rect.y = 90;
    but.rect.w = 450;
    but.rect.h = 80;
    buttons[0] = but;
    surf = IMG_Load("./Assets/buttons/button2.png");
    but.txt = SDL_CreateTextureFromSurface(r,surf);
    SDL_FreeSurface(surf);
    but.rect.x = 500;
    but.rect.y = 90 + 100;
    but.rect.w = 450;
    but.rect.h = 80;
    buttons[1] = but;
    surf = IMG_Load("./Assets/buttons/button3.png");
    but.txt = SDL_CreateTextureFromSurface(r,surf);
    SDL_FreeSurface(surf);
    but.rect.x = 500;
    but.rect.y = 90 + 200;
    but.rect.w = 450;
    but.rect.h = 80;
    buttons[2] = but;
    surf = IMG_Load("./Assets/buttons/button4.png");
    but.txt = SDL_CreateTextureFromSurface(r,surf);
    SDL_FreeSurface(surf);
    but.rect.x = 500;
    but.rect.y = 90 + 300;
    but.rect.w = 450;
    but.rect.h = 80;
    buttons[3] = but;
}

void Buttons::render(){
    SDL_RenderCopy(ren,buttons[0].txt,NULL,&buttons[0].rect);
    SDL_RenderCopy(ren,buttons[1].txt,NULL,&buttons[1].rect);
    SDL_RenderCopy(ren,buttons[2].txt,NULL,&buttons[2].rect);
    SDL_RenderCopy(ren,buttons[3].txt,NULL,&buttons[3].rect);
}

void Buttons::handleMouseMove(int x, int y){
    bool is_found = true;
    for(int a = 0; a < 4; a++){
        const int b_x = buttons[a].rect.x;
        const int b_y = buttons[a].rect.y;
        if(x > b_x and x < b_x + buttons[a].rect.w and y > b_y and y < b_y + buttons[a].rect.h){
            buttons[a].rect.w = 470;
            buttons[a].rect.h = 90;
            buttons[a].rect.x = 490;
            buttons[a].rect.y = 85 + a*100;
            SDL_SetCursor(cur1);
            is_found = false;
        }else{
            buttons[a].rect.w = 450;
            buttons[a].rect.h = 80;
            buttons[a].rect.x = 500;
            buttons[a].rect.y = 90 + a*100;
        }
    }
    if(is_found){
        SDL_SetCursor(cur2);
    }
}