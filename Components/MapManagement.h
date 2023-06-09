#include "../Helpers/All.h"
#include "../Helpers/Colors.h"
#include "./Field.h"
#include "./Board.h"

#ifndef MapManagement_h
#define MapManagement_h

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

class MapManagement{
    public:
        MapManagement(SDL_Renderer *renderer);
        ~MapManagement();

        void renderMap();
        void higher_render();

        void set_map(int map[12][18]);
        int get_map_field(int col, int row);
        void set_map_field(int value, int col, int row);
        int get_map_field_id(int x, int y);
        int get_map_field_by_coords(int x_cor, int y_cor, int &col, int &row);
        void handle_mouse_movement(int x, int y);
        void handle_mouse_click(int x, int y);

        void find_path_from(int x, int y,int curr_x , int curr_y, std::vector<std::string> &moves);

        static const int F_SIZE = 60;
        static const int WIDTH = WINDOW_WIDTH / F_SIZE;
        static const int HEIGHT = WINDOW_HEIGHT / F_SIZE;

    private:
        int **board;
        std::string rim_color;
        Field *field = nullptr;
        std::vector<Board*> board_objects;
        SDL_Renderer *ren;

        struct M_field{
            bool checked;
            int occupied;
        };

        struct f_check{
            int x;
            int y;
            int parent_id;
        };

        std::vector<f_check> path_finder(int x, int y, int d_x, int d_y);

        int base_map[12][18] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,1},
            {1,4,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,1},
            {1,4,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,4,0,2,99,0,2,0,0,2,0,0,2,0,0,0,0,1},
            {1,4,0,2,99,0,2,0,0,2,0,0,2,0,0,0,0,1},
            {1,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,1},
            {1,5,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
};

#endif