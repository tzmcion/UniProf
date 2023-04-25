#include "../Assets/All.h"

#include "./Timer.h"
#include "../Helpers/Colors.h"

class Character{
    public:
        Character(SDL_Renderer *r,const char* img_path,int width, int height, std::string name = "Character");
        ~Character();


        void add_phase(const char* img_path);
        void set_phase(int number);
        void set_static_position(int x, int y, int field_size);
        void update(int F_SIZE);
        void render();

        int get_x_pos();
        int get_y_pos();

        struct Phase{
            SDL_Texture *texture;
            SDL_Rect rect;
        };
        Timer *timer = nullptr, *phase_timer = nullptr;
        std::vector<Phase> phases;
        std::vector<SDL_Texture* > textures; 
        SDL_Renderer *ren;
        SDL_Surface *surface;
        SDL_Texture *texture_swp;
        int phase_number = 0, phases_length = 0, current_tex = 0;
        bool is_basic_phase = true;
};