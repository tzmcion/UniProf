#ifndef Character_h
#define Character_h

#include "../Helpers/All.h"
#include "./Timer.h"
#include "../Helpers/Colors.h"
#include "./Messenger.h"

class Character{
    public:
        Character(SDL_Renderer *r,const char* img_path,int width, int height, std::string name = "Character");
        ~Character();


        void add_phase(const char* img_path);
        void set_phase(int number);
        void set_static_position(int x, int y, int field_size);
        void set_answers(std::string data[], int answers_quantity);
        void update(int F_SIZE);
        void render();
        void cloud_if_has_mouse(int x, int y);

        int get_x_pos();
        int get_y_pos();


        struct Character_Data{
            SDL_Texture *texture;
            SDL_Rect rect;
            bool render;
        };
        Timer *timer = nullptr, *phase_timer = nullptr;
        Character_Data c_data;
        std::vector<SDL_Texture* > textures;
        std::vector<Character_Data> additional_renders;
        SDL_Renderer *ren;
        SDL_Surface *surface;
        SDL_Texture *texture_swp;
        Messenger *messenger = nullptr;
        int current_tex = 0;
        bool is_basic_phase = true, render_message = false;
        std::string *answers = nullptr;
        int which_answer = 0, answers_sum = 7;
};

#endif