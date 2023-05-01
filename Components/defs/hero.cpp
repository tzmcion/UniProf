#include "../hero.h"

using namespace Colors;

Hero::Hero(SDL_Renderer *r,const char* img_path,int width, int height):   Character(r, img_path, width, height, "HERO"){
    walk_anim_timer = new Timer();
    timer->start();
    refil = new Timer();
    refil->start();
    add_phase("./Assets/hero/hero3.png");
    add_phase("./Assets/hero/hero_walk_1.png");
    add_phase("./Assets/hero/hero_walk_2.png");
};

Hero::~Hero(){};

void Hero::set_position(std::vector<std::string> moves, int F_SIZE){
    int l_x = c_data.rect.x / F_SIZE;
    int l_y = c_data.rect.y / F_SIZE;
    if(dests.size() > 0){
            destination_data a = dests[0];
            dests.clear();
            dests.push_back(a);
            if(a.direction == 'x'){
                l_x = std::round(double(l_x) + std::round(double(a.direction)*1));
            }else{
                l_y = std::round(double(l_y) + std::round(double(a.direction)*1));
        }
    }
    for(int x = moves.size()-1; x >= 0; x--){
        const std::string destination = moves[x].substr(0,moves[x].find(" "));
        int move =  std::stoi(moves[x].substr(moves[x].find(" ")+1 ,moves[x].length()));
        if(move == 11){move = -1;}
        destination_data data;
        if(destination == "X"){
            data.direction = 'x';
            data.position = F_SIZE * move;
        }else{
            data.direction = 'y';
            data.position = F_SIZE *  move;
        }
        dests.push_back(data);
    }
    // }
    // for(int b = 1; b < std::abs(l_x - x)+1; b++){
    //     destination_data data;
    //     data.direction = 'x';
    //     if(l_x < x){
    //         data.position = F_SIZE;
    //         data.x_dest = b + l_x;
         
    //     }else{
    //         data.position = -1 * F_SIZE; 
    //         data.x_dest = b*-1 + l_x;
        
    //     }
    //     data.y_dest = 0;
    //     dests.push_back(data);
    // }
    // for(int a = 1; a < std::abs(l_y - y)+1; a++){
    //     destination_data data;
    //     data.direction = 'y';
    //     if(l_y < y){
    //         data.position = F_SIZE;
    //         data.y_dest = l_y; 
    //     }else{
    //         data.position = -1 * F_SIZE;
    //         data.y_dest = a*-1 + l_y; 
    //     }
    //     data.x_dest = 0;
    //     dests.push_back(data);
    // }
}

void Hero::update(int F_SIZE){
    set_phase(dests.size());
    if(!ismoving){
        if(dests.size() > 0){
            last_x = c_data.rect.x;
            last_y = c_data.rect.y;
            ismoving = true;
            timer->start();
        }
    }
    if(ismoving && energy > 0){
        if(dests[0].direction == 'x'){
            Move_vertically_in_time(dests[0].position, move_time);
        }else{
            Move_horizontally_in_time(dests[0].position, move_time);
        }
    }
    if(energy <=1){
        dests.clear();
    }
    int time = int(refil->get());
    if(time > 250 and !ismoving){
        refil->start();
        if(energy +2 <= 100){
            energy+=2;
        }
        if(patience + 2 <= 100){
            patience+=2;
        }
    }
    handle_walk_phase_change();
}

//Private

void Hero::handle_walk_phase_change(){
    if(ismoving){
        is_basic_phase = false;
        if(walk_anim_timer->get() > 300){
            c_data.texture = textures[walk_anim_id];
            walk_anim_id + 1 > 3 ? walk_anim_id = 2: walk_anim_id += 1;
            walk_anim_timer->start();
        }
    }else{
        is_basic_phase = true;
    }
}


void Hero::Move_vertically_in_time(int dest_x, double milliseconds){
    double percentage = timer->get()/milliseconds;
    c_data.rect.x = std::round(double(last_x) + std::round(double(dest_x)*percentage));
    if(percentage >= 1){
        energy -= 4;
        ismoving = false;
        dests.erase(dests.begin());
        c_data.rect.x = last_x + dest_x;
    }
}

void Hero::Move_horizontally_in_time(int dest_y, double milliseconds){
    double percentage = timer->get()/milliseconds + 0.05;
    c_data.rect.y = std::round(double(last_y) + std::round(double(dest_y)*percentage));
    if(percentage >= 1){
        energy -= 4;
        ismoving = false;
        dests.erase(dests.begin());
        c_data.rect.y = last_y + dest_y;
    }
}