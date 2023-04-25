#include "../character.h"

using namespace Colors;

Character::Character(SDL_Renderer *r,const char* img_path,int width, int height, std::string name){
    RESET("Creating character '" + name + "'... ");
    ren = r;
    try{
        surface = IMG_Load(img_path);
        if(!surface){
            throw(name);
        }else{
            GREEN("[DONE]\n");
        }
    }
    catch(std::string c){
        RED("[ERROR WRONG PATH IN CHARACTER " + c + "]");
        BLUE(" Generating Default Asset in exchange... \n");
        surface = IMG_Load("./Assets/laughing.png");
    }
    Phase ph;
    ph.rect.w = width;
    ph.rect.h = height;
    ph.rect.x = 60;
    ph.rect.y = 60;
    ph.texture = SDL_CreateTextureFromSurface(ren,surface); 
    textures.push_back(ph.texture);
    phases.push_back(ph);
    SDL_FreeSurface(surface);
    timer = new Timer();
    phase_timer = new Timer();
    phases_length++;
    phase_timer->start();
}

Character::~Character(){}

void Character::add_phase(const char* img_path){
    RESET("adding phase to  "+ std::string(img_path) +"... ");
    try{
        surface = IMG_Load(img_path);
        if(!surface){
            throw("phase 2");
        }else{
            GREEN("[DONE]\n");
        }
    }
    catch(std::string c){
        RED("[ERROR WRONG PATH IN CHARACTER " + c + "]");
        BLUE(" Generating Default Asset in exchange... \n");
        surface = IMG_Load("./Assets/laughing.png");
    }
    textures.push_back(SDL_CreateTextureFromSurface(ren,surface));
    SDL_FreeSurface(surface);
    phases_length++;
}


void Character::set_phase(int number){
    if(phase_timer->get() >= rand() % 600 + 1000 && is_basic_phase && number == 0){
        phases[phase_number].texture = textures[current_tex];
        if(current_tex +1 < 2){
            current_tex+=1;
        }else{
            current_tex = 0;
        }
        phase_timer->start();
    }
}

void Character::set_static_position(int x, int y, int field_size){
    phases[phase_number].rect.x = x * field_size;
    phases[phase_number].rect.y = y * field_size;
}

void Character::update(int F_SIZE){
    set_phase(0);
}

void Character::render(){
    SDL_RenderCopy(ren,phases[phase_number].texture,NULL,&phases[phase_number].rect);
}

int Character::get_x_pos(){
    return Character::phases[phase_number].rect.x;
}

int Character::get_y_pos(){
    return Character::phases[phase_number].rect.y;
}

//Private Functions
