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
    hero = new Hero(renderer,"./Assets/hero/hero2.png",MapManagement::F_SIZE*0.8,MapManagement::F_SIZE*0.95);
    characters.push_back(new Character(renderer,"./Assets/Char2/c1.png",MapManagement::F_SIZE,MapManagement::F_SIZE,"Character 1"));
    characters.push_back(new Character(renderer,"./Assets/Char1/c1.png",MapManagement::F_SIZE,MapManagement::F_SIZE,"Character 1"));
    st = new Static_objects(renderer);
    hero->add_phase("./Assets/hero/hero3.png");
    hero->add_phase("./Assets/hero/hero_walk_1.png");
    hero->add_phase("./Assets/hero/hero_walk_2.png");
    characters[0]->add_phase("./Assets/Char2/c2.png");
    characters[1]->add_phase("./Assets/Char1/c2.png");
    characters[0]->set_static_position(4,5,MapManagement::F_SIZE);
    characters[1]->set_static_position(4,7,MapManagement::F_SIZE);
    st->add_static_object("../Assets/Rim.png",10,550,700*0.8,200*0.8);
    st->add_static_object("./Assets/hero/hero_face.png",20,555,200*0.7,200 *0.7);
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
            Input_Manager::handle_mouse_click(hero,map);
        case SDL_MOUSEMOTION:
            int x,y;
            SDL_GetMouseState(&x,&y);
            for(int a = 0; a < characters.size(); a++){
                Input_Manager::handle_mouse_movement(characters[a],x,y);
            }
            Input_Manager::handle_mouse_movement(hero,x,y);
            break;
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
