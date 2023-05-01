#include "./Base_Level.h"
#include "../Components/Buttons.h"

class Level_one : public Base_Level{
    public:
        Level_one();
        ~Level_one();

        void Init(SDL_Renderer *renderer);
        void Update();
        void Render(); 
        void MouseDown();
        void MouseMove();
    private:
        SDL_Renderer *ren = nullptr;
        Static_objects *st_manager = nullptr;
        MapManagement *map = nullptr;
        Hero *hero = nullptr;
        Timer *timer = nullptr;
        Buttons *buttons = nullptr;
        std::vector<Character*> characters;

        int progress;
        const int f_size = MapManagement::F_SIZE;
        int level_map[12][18] = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,4,0,2,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,4,0,2,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,4,0,2,99,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,4,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,2,99,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,4,0,2,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,4,0,2,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
};