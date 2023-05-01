#pragma once
#include "../Helpers/All.h"

class Static_objects{
    public:
        Static_objects(SDL_Renderer *ren);
        ~Static_objects();

        void add_static_object(const char *path, int x_pos, int y_pos, int width, int height);
        void render(int stamina, int energy);

    private:
        SDL_Renderer *ren;
        SDL_Surface *surf;
        SDL_Texture *txt;

        struct Objects{
            SDL_Texture *texture;
            SDL_Rect rect;
        };

        std::vector<Objects> objects;
        
};  