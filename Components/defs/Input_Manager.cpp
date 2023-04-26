#include "../Input_Manager.h"

void Input_Manager::handle_mouse_movement(Character *character, int x, int y){
    character->cloud_if_has_mouse(x,y);
}

void Input_Manager::handle_mouse_click(Hero *hero, MapManagement *map){
    int x,y;
    SDL_GetMouseState(&x,&y);
    map->get_map_field_by_coords(x,y,x,y);
    if(map->get_map_field_id(x,y) == 0){
        std::vector<std::string> moves;
        map->find_path_from(x,y,hero->get_x_pos() / MapManagement::F_SIZE,hero->get_y_pos() / MapManagement::F_SIZE,moves);
        hero->set_position(moves,MapManagement::F_SIZE);
    }
}