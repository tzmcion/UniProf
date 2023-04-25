#include "./Components/engine.h"

Engine *engine = nullptr;
int main(){
    srand(time(NULL));
    const int FPS = 120;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    engine = new Engine("Uni Prof",50,50,WINDOW_WIDTH,WINDOW_HEIGHT,NULL);
    while(engine->isRunning){
        frameStart = SDL_GetTicks();
        engine->HandleEvents();
        engine->Update();
        engine->Render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    engine->Clean();
    return 0;


}