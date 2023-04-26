#include <SDL2/SDL.h>
#include "./Helpers.h"
#include "./hero.h"
#include "./MapManagement.h"
#include "./static_objects.h"
#include "./Input_Manager.h"

class Engine{
    public:
        Engine(const char* title, int x_pos, int y_pos ,int width, int height, Uint32 flags);
        ~Engine();

        void init();

        void HandleEvents();
        void Update();
        void Render();
        void Clean();

        bool isRunning = true;
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        Static_objects *st = nullptr;
        std::vector<Character*> characters;

        MapManagement *map = nullptr;
        Hero *hero = nullptr;
};