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
    Character_Data ph;
    ph.rect.w = width;
    ph.rect.h = height;
    ph.rect.x = 60;
    ph.rect.y = 60;
    ph.texture = SDL_CreateTextureFromSurface(ren,surface); 
    textures.push_back(ph.texture);
    c_data = ph;
    SDL_FreeSurface(surface);
    timer = new Timer();
    phase_timer = new Timer();
    phase_timer->start();

    messenger = new Messenger(ren,"./Assets/fonts/Roboto-Regular.ttf", "./Assets/chat.png",8);
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
}


void Character::set_phase(int number){
    if(phase_timer->get() >= rand() % 600 + 1000 && is_basic_phase && number == 0){
        c_data.texture = textures[current_tex];
        if(current_tex +1 < 2){
            current_tex+=1;
        }else{
            current_tex = 0;
        }
        phase_timer->start();
    }
}

void Character::set_static_position(int x, int y, int field_size){
    c_data.rect.x = x * field_size;
    c_data.rect.y = y * field_size;
}

void Character::update(int F_SIZE){
    set_phase(0);
}

void Character::render(){
    SDL_RenderCopy(ren,c_data.texture,NULL,&c_data.rect);
    if(render_message){
        messenger->write(answers[which_answer],c_data.rect.x + c_data.rect.w/1.3,c_data.rect.y - c_data.rect.h/2);
    }
}

int Character::get_x_pos(){
    return Character::c_data.rect.x;
}

int Character::get_y_pos(){
    return Character::c_data.rect.y;
}

void Character::cloud_if_has_mouse(int x, int y){
    render_message = false;
    if(x > c_data.rect.x && x < c_data.rect.x + c_data.rect.w){
        if(y > c_data.rect.y && y < c_data.rect.y + c_data.rect.h){
           render_message = true;
        }
    }
    if(!render_message){
        which_answer = rand()% answers_sum;
    }
}

void Character::set_answers(std::string data[], int answers_quantity){
    answers = new std::string[answers_quantity];
    for(int x = 0; x < answers_quantity; x++){
        answers[x] = data[x];
    }
    answers_sum = answers_quantity;
}

//Private Functions
