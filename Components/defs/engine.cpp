#include "../engine.h"

using namespace Colors;

Engine::Engine(const char* title, int x_pos, int y_pos ,int width, int height, Uint32 flags){
    std::vector <std::string> front_data = get_array_from_file("./Data/Authors.txt");
    for(int i = 0; i < front_data.size(); i++){
        std::cout << front_data[i].substr(0, front_data[i].find(":")+1) << " " << front_data[i].substr(front_data[i].find(":")+1,front_data[i].length()) <<std::endl;
    }
    RESET("\nGraphic engine... ");
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        GREEN("[READY]");
        RESET("\nGame window... ");
        window = SDL_CreateWindow(title,x_pos,y_pos,width,height,flags);
        if(window) GREEN("[READY]");
        RESET("\nRender object...");
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer) GREEN("[READY]\n");
        WHITE("Initializing Game Loop...\n");
    }
    hero = new Hero(renderer,"./Assets/hero2.png",MapManagement::F_SIZE*0.85,MapManagement::F_SIZE*1);
    characters.push_back(new Character(renderer,"./Assets/Char2/c1.png",MapManagement::F_SIZE,MapManagement::F_SIZE,"Character 1"));
    characters.push_back(new Character(renderer,"./Assets/Char1/c1.png",MapManagement::F_SIZE,MapManagement::F_SIZE,"Character 1"));
    st = new Static_objects(renderer);
    hero->add_phase("./Assets/hero3.png");
    hero->add_phase("./Assets/hero_walk_1.png");
    hero->add_phase("./Assets/hero_walk_2.png");
    characters[0]->add_phase("./Assets/Char2/c2.png");
    characters[1]->add_phase("./Assets/Char1/c2.png");
    characters[0]->set_static_position(4,5,MapManagement::F_SIZE);
    characters[1]->set_static_position(4,6,MapManagement::F_SIZE);
    st->add_static_object("../Assets/Rim.png",10,550,700*0.8,200*0.8);
    st->add_static_object("./Assets/hero_face.png",20,555,200*0.7,200 *0.7);
    map = new MapManagement(renderer);
}

Engine::~Engine(){}

void Engine::init(){
    delete hero;
}

void Engine::HandleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x,y;
            SDL_GetMouseState(&x,&y);
            map->get_map_field_by_coords(x,y,x,y);
            if(map->get_map_field_id(x,y) == 0){
                std::vector<std::string> moves;
                map->find_path_from(x,y,hero->get_x_pos() / MapManagement::F_SIZE,hero->get_y_pos() / MapManagement::F_SIZE,moves);
                hero->set_position(moves,MapManagement::F_SIZE);
            }
        default:
            break;
    }
}

void Engine::Update(){
    hero->update(MapManagement::F_SIZE);
    for(int x = 0; x < characters.size();x++){
        characters[x]->update(MapManagement::F_SIZE);
    }
}

void Engine::Render(){
    SDL_RenderClear(renderer);
    map->renderMap();
    hero->render();
     for(int x = 0; x < characters.size();x++){
        characters[x]->render();
    }
    st->render(hero->get_stamina(),hero->get_patience());
    SDL_RenderPresent(renderer);
}

void Engine::Clean(){
    RESET("\nExiting program... ");
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    GREEN("[DONE]");
    RESET("\n");
}
