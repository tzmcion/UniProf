#include "../Level1.h"

Level_one::Level_one(){};

Level_one::~Level_one(){
    delete st_manager;
    delete map;
    delete hero;
    delete timer;
    for(int x = 0; x < characters.size(); x++){
        delete characters[x];
    }
}

void Level_one::Init(SDL_Renderer *renderer){
    ren = renderer;
    hero = new Hero(ren,"./Assets/hero/hero2.png",f_size*0.8,f_size*0.95);
    st_manager = new Static_objects(renderer);
    map = new MapManagement(renderer);
    timer = new Timer();
    buttons = new Buttons(ren);
    std::string answers[2] = {"what?", "cool"};
    for(int x = 0; x < 2; x++){
        std::string path = "./Assets/Char" + std::to_string(x+1) + "/c@.png";
        int index = path.find('@');
        path.replace(index,1,"1");
        characters.push_back(new Character(ren, path.c_str(),f_size,f_size,"Character " + std::to_string(x)));
        path.replace(index,1,"2").c_str();
        characters[x]->add_phase(path.c_str());
        characters[x]->set_static_position(4,x*4+3,f_size);
        characters[x]->set_answers(answers,2);
    }
    hero->set_answers(answers,2);
    map->set_map(level_map);
}

void Level_one::Update(){
    const int x_pos = hero->get_x_pos() / f_size;
    const int y_pos = hero->get_y_pos() / f_size;
    if(x_pos == 1 && (y_pos == 2 || y_pos == 3 || y_pos == 5 || y_pos == 6 ) && timer->get() > 500){
        progress+=1;
        timer->start();
    }
    hero->update(MapManagement::F_SIZE);
    for(int x = 0; x < characters.size();x++){
        characters[x]->update(MapManagement::F_SIZE);
    }
}

void Level_one::MouseDown(){
    int x,y;
    SDL_GetMouseState(&x,&y);
    Input_Manager::handle_mouse_click(hero,map);
    map->handle_mouse_click(x,y);
}

void Level_one::MouseMove(){
    int x,y;
    SDL_GetMouseState(&x,&y);
    for(int a = 0; a < characters.size(); a++){
        Input_Manager::handle_mouse_movement(characters[a],x,y);
    }
    Input_Manager::handle_mouse_movement(hero,x,y);
    buttons->handleMouseMove(x,y);
    map->handle_mouse_movement(x,y);
}

void Level_one::Render(){
    map->renderMap();
    hero->render();
     for(int x = 0; x < characters.size();x++){
        characters[x]->render();
    }
    buttons->render();
    map->higher_render();
};