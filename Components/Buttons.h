#pragma once
#include "../Helpers/All.h"

class Buttons{
    public:
        Buttons(SDL_Renderer *r);
        ~Buttons();

        void handleClick();
        void handleMouseMove(int x, int y);
        void render();
    private:
        SDL_Surface *surf;
        SDL_Renderer *ren;
        struct Button{
            SDL_Texture *txt;
            SDL_Rect rect;
        };
        Button buttons[4];
        SDL_Cursor *cur1,*cur2;
};