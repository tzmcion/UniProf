#pragma once
#include "../Helpers/All.h"
#include "./Messenger.h"
#include "./Timer.h"

class Board{
    public:
        Board(SDL_Renderer *renderer,int x,int y, int s);
        ~Board();

        void render();
        void handle_mouseclick(int x, int y);
        void handle_mouseover(int x, int y);

        int get_progress(){return progress;}
        bool is_open(){return open;}
    private:

        SDL_Renderer *ren;
        SDL_Texture *minimap_tex, *green_bg, *orange_bg, *big_board;
        SDL_Surface *surf;
        Messenger *messenger = nullptr;
        Timer *timer = nullptr;
        SDL_Rect rect,big_board_rect;
        int progress = 0, size;
        bool open = false, mouse_over = false, is_opening = false;
        void draw_board_from_top(int dest_y, double time);

        struct Equation{
            SDL_Texture *texture;
            SDL_Rect rect, answers_rect;
            std::string equation, answers[4];
            int good_answer, good_answer_id;
            int width[4], height[4];
        };

        const char operators[3] = {'+', '-', '*'};
        Equation equation;
        void generate_equation();
        void write_equation();
};