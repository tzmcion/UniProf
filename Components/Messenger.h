#include "../Assets/All.h"

#ifndef messenger_h
#define messenger_h

class Messenger{
    public:
        Messenger(SDL_Renderer *r, const char* font_path, const char* img_path, int font_size);
        ~Messenger();

        void write(std::string txt, int x, int y);
        void set_color(Uint8[3]);

    private:
        TTF_Font *font = nullptr;
        SDL_Color color;
        SDL_Rect rect;
        SDL_Texture *message, *bg;
        SDL_Surface *surf;
        SDL_Renderer *ren;
};

#endif