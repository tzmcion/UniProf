#include "../Assets/All.h"

class Field{
    public:
        Field(SDL_Renderer *r, std::vector<std::string>paths, int width, int height);
        ~Field();


        /*  Function renders Field as wall/floor or anything
        *   it gets the id of a field and renders the image
        *   signed to that id in x and y arguments determined
        */
        void render_field(int id,int x,int y);

    private:
        SDL_Renderer*ren;
        SDL_Rect rect;
        SDL_Surface *surf;
        std::vector<SDL_Texture* > textures;
};
