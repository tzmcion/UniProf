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
    levels[0] = new Level_one();
    levels[current_level]->Init(renderer);
}

Engine::~Engine(){}

void Engine::HandleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            levels[current_level]->MouseDown();
        case SDL_MOUSEMOTION:
            int x,y;
            levels[current_level]->MouseMove();
            break;
        default:
            break;
    }
}

void Engine::Update(){
    levels[current_level]->Update();
}

void Engine::Render(){
    SDL_RenderClear(renderer);
    levels[current_level]->Render();
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
