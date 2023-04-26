#include "../Assets/All.h"
#include "./character.h"
#include "./MapManagement.h"
#include "./hero.h"

class Input_Manager{
    public:
        static void handle_mouse_movement(Character *character,int x, int y);
        static void handle_mouse_click(Hero *hero, MapManagement *map);
};