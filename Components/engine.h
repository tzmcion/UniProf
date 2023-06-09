#include <SDL2/SDL.h>
#include "./Helpers.h"
#include "./hero.h"
#include "./MapManagement.h"
#include "./static_objects.h"
#include "./Input_Manager.h"
#include "../Levels/Base_Level.h"
#include "../Levels/Level1.h"

class Engine{
    public:
        Engine(const char* title, int x_pos, int y_pos ,int width, int height, Uint32 flags);
        ~Engine();

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

        Base_Level *levels[10];
        int current_level = 0;
};