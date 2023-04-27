#include "character.h"

#ifndef Hero_h
#define Hero_h

class Hero : public Character{

    public:
        Hero(SDL_Renderer *r,const char* img_path,int width, int height);
        ~Hero();

        int get_stamina(){return energy;};
        int get_patience(){return patience;};
        void set_position(std::vector<std::string> moves, int F_SIZE);
        void update(int F_SIZE);
    private:
        int patience = 100;
        int energy = 100;
        const std::string answers[7] = {"kay","heh, that's me", "love you", "what the hell man OMG", "I was there", "FFL - Fortran For Life"};
        //So the stamina will be getting less and less empty every second character moves
        Timer *refil = nullptr;
        //Functions and variables for animations
        struct destination_data{
            char direction;
            int position;
            int x_dest;
            int y_dest;
        };
        std::vector<destination_data> dests;
        int last_x, last_y;

        void Move_vertically_in_time(int dest_x, double milliseconds);
        void Move_horizontally_in_time(int dest_y, double milliseconds);
        void handle_walk_phase_change();
        bool ismoving = false;
        Timer *walk_anim_timer = nullptr;
        int walk_anim_id = 2;
        const int move_time = 160;
};

#endif