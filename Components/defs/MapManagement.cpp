#include "../MapManagement.h"

using namespace Colors;

MapManagement::MapManagement(SDL_Renderer *renderer){
    ren = renderer;
    board = new int*[WIDTH];
    RESET("\nGenerating map... ");
    for (int i = 0; i < WIDTH; ++i) {
        board[i] = new int[HEIGHT];
        for(int j = 0; j < HEIGHT; j++){
               board[i][j] = base_map[j][i];
        }
    }
    GREEN("[DONE]");
    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
    RESET("\nLoading Textures for Walls\Floor... ");
    std::vector<std::string> paths = {"./Assets/floor.png", "./Assets/wall.png", "./Assets/desk.png","./Assets/toilet_paper.png","./Assets/board.png","./Assets/trash.png"};
    field = new Field(ren,paths,F_SIZE,F_SIZE);
    GREEN("[DONE]");

};

MapManagement::~MapManagement(){}

int MapManagement::get_map_field_id(int x, int y){
    if(x < WIDTH && y < HEIGHT){
        return board[x][y];
    }
}

void MapManagement::renderMap(){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            field->render_field(board[x][y],x * F_SIZE, y * F_SIZE);
        }
    }
}

int MapManagement::get_map_field_by_coords(int x_cor, int y_cor, int &col, int &row){
    col = x_cor / F_SIZE;
    row = y_cor / F_SIZE;
}

void MapManagement::find_path_from(int x, int y, int curr_x,int curr_y ,std::vector<std::string> &moves){
    std::string start_dest;
    if(curr_x - x > 0){
        start_dest="x-";
    }else{
        start_dest="x1";
    }
    //moves = requrency_path_finder(x,y,curr_x,curr_y,start_dest);
    std::vector<std::string> m_moves;
    std::vector<f_check> mvs;
    mvs = path_finder(curr_x,curr_y,x,y);
    int last_x = x, last_y = y;
    for(int x = 0; x < mvs.size(); x++){
        std::string move;
        if(mvs[x].x != last_x){
            move += 'X';
            move += ' ';
            move += mvs[x].x < last_x ? "1" : "-1";
        }
        if(mvs[x].y != last_y){
            move += 'Y';
            move += ' ';
            move += mvs[x].y < last_y ? "1" : "-1";
        }
        last_x = mvs[x].x;
        last_y = mvs[x].y;
        m_moves.push_back(move);
    }
    moves = m_moves;
}

//Private functions

//Path Finding

std::vector<MapManagement::f_check> MapManagement::path_finder(int x, int y, int d_x, int d_y){
    //So basically from every parent field creates fields that were not checked
    //If the field was checked, no child field is created there

    const int map_height = WIDTH;
    const int map_width = HEIGHT;

    M_field **fields = new M_field*[map_height];
    for(int a = 0; a<map_height; a++){
        fields[a] = new M_field[map_width];
        for(int b = 0; b < map_width; b++){
            fields[a][b].checked = false;
            fields[a][b].occupied = board[a][b];
        }
    }

    std::vector<f_check> checks;
    bool is_found = false;
    f_check parent;
    parent.x = x;
    parent.y = y;
    parent.parent_id = -1;
    checks.push_back(parent);
    int found_id = 0, counter = 0;
    while(!is_found){
        counter++;
        for(int a = 0; a < checks.size(); a++){
            if(checks[a].x == d_x and checks[a].y == d_y){
                is_found = true;
                found_id = a;
                break;
            }
            int c_x = checks[a].x, c_y = checks[a].y;
            f_check this_check;
            //Try go up
            c_x++;
            if(c_x < map_height and fields[c_x][c_y].checked == false and fields[c_x][c_y].occupied == 0){
                this_check.x = c_x;
                this_check.y = c_y;
                this_check.parent_id = a;
                checks.push_back(this_check);
                fields[c_x][c_y].checked = true;
            }
            c_x--;
            //Try to lo down
            c_x--;
            if(c_x < map_height and fields[c_x][c_y].checked == false and fields[c_x][c_y].occupied == 0){
                this_check.x = c_x;
                this_check.y = c_y;
                this_check.parent_id = a;
                checks.push_back(this_check);
                fields[c_x][c_y].checked = true;
            }
            c_x++;
            //Try to go up
            c_y++;
            if(c_y < map_width and fields[c_x][c_y].checked == false and fields[c_x][c_y].occupied == 0){
                this_check.x = c_x;
                this_check.y = c_y;
                this_check.parent_id = a;
                checks.push_back(this_check);
                fields[c_x][c_y].checked = true;
            }
            c_y--;
            //Try to go down
            c_y--;
            if(c_y < map_width and fields[c_x][c_y].checked == false and fields[c_x][c_y].occupied == 0){
                this_check.x = c_x;
                this_check.y = c_y;
                this_check.parent_id = a;
                checks.push_back(this_check);
                fields[c_x][c_y].checked = true;
            }
        }
        if(counter > 1000){
            checks.clear();
            return checks;
        }
    }
    std::vector<f_check> moves;
    while(1){
        found_id = checks[found_id].parent_id;
        moves.push_back(checks[found_id]);
        if(checks[found_id].parent_id == -1){
            break;
        }
    }
    
    return moves;

}