#pragma once
#include "../Helpers/All.h"
#include "../Components/character.h"
#include "../Components/MapManagement.h"
#include "../Components/hero.h"
#include "../Components/static_objects.h"
#include "../Components/Input_Manager.h"

class Base_Level{
    public:
        virtual void Init(SDL_Renderer *renderer);
        virtual void Update();
        virtual void Render(); 
        virtual void MouseDown();
        virtual void MouseMove();
};