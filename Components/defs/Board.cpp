#include "../Board.h"

Board::Board(SDL_Renderer *renderer,int x, int y, int s){
    ren = renderer;
    rect.x = x * s;
    rect.y = y * s;
    rect.w = s;
    rect.h = s;
    big_board_rect.w = 800;
    big_board_rect.h = 500;
    big_board_rect.x = 150;
    equation.rect.y = 100;
    equation.rect.x = 200;
    equation.answers_rect.x = 400;
    equation.answers_rect.y = 100;
    size = s;
    minimap_tex = Texture_Loader::create_texture(ren,"./Assets/map/board.png");
    green_bg = Texture_Loader::create_texture(ren,"./Assets/gradients/green.png");
    orange_bg = Texture_Loader::create_texture(ren,"./Assets/gradients/orange.png");
    big_board = Texture_Loader::create_texture(ren,"./Assets/gradients/full_board.png");
    messenger = new Messenger(ren,"./Assets/fonts/Roboto-Light.ttf","/",8);
    SDL_SetTextureAlphaMod(big_board,220);
    timer = new Timer();
}

Board::~Board(){

}

void Board::handle_mouseclick(int x, int y){
    if(!open){
        if(x > rect.x and x < rect.x + rect.w and y > rect.y and y < rect.y + rect.h){
            big_board_rect.y = -1000;
            is_opening = true;
            timer->start();
        }
    }else{
        if(x > big_board_rect.x and x < big_board_rect.x + big_board_rect.w and y > big_board_rect.y and y < big_board_rect.y + big_board_rect.h){
            //Handle click on the big board
            if(progress < 100){
                for(int a = 0; a < 4; a++){
                    if(x > equation.answers_rect.x + 80*a and x < equation.answers_rect.x + 80*a + equation.width[a]){
                        if( y > equation.answers_rect.y and y < equation.answers_rect.y + equation.height[a]){
                            if(equation.answers[a] == std::to_string(equation.good_answer)){
                                progress+=20;
                            }else{
                                if(progress -5 >=0){
                                    progress-=5;
                                }
                            }
                            generate_equation();
                        }
                    }
                }
            }
        }else{
            open = false;
        }
    }
}

void Board::handle_mouseover(int x, int y){
    mouse_over = false;
    if(x > rect.x and x < rect.x + rect.w and y > rect.y and y < rect.y + rect.h){
        mouse_over = true;
    }
}

void Board::render(){
    if(!open){
        if(mouse_over){
            if(progress< 100){
                SDL_RenderCopy(ren,orange_bg,NULL,&rect);
                messenger->write_blank(std::to_string(progress) + "%",rect.x + 15, rect.y + 20);
            }else{
                SDL_RenderCopy(ren,green_bg,NULL,&rect);
            }
        }
    }
    SDL_RenderCopy(ren,minimap_tex,NULL,&rect);
    if(is_opening || open){
        if(is_opening){
            draw_board_from_top(1020,700);
        }
        SDL_RenderCopy(ren,big_board,NULL,&big_board_rect);
        if(open){
            write_equation();
        }
    }
}

//Private

void Board::draw_board_from_top(int dest_y, double time){
    double current_time = timer->get();
    double percentage = (current_time/time);
    big_board_rect.y = int(dest_y*sin(90*3.14/180*percentage)) - 1000;
    if(percentage >= 1){
        is_opening = false;
        open = true;
        generate_equation();
    }
}

void Board::generate_equation(){
    const int first = rand() % 50;
    const int second = rand() % 50;
    //here, create good answers and equation
    char oper_type = operators[rand()%3];
    if(oper_type == '+'){
        equation.good_answer = first + second;
    }else if(oper_type == '-'){
        equation.good_answer = first - second;
    }else if(oper_type == '*'){
        equation.good_answer = first * second;
    }
    equation.equation = std::to_string(first) + " " + oper_type + " " + std::to_string(second) + " = ";
    //Here, generate the answers
    for(int x = 0; x < 4; x++){
        equation.answers[x] = std::to_string(equation.good_answer + (rand() % 2 == 0 ? (rand()%30) : ((rand()%30) * -1)));
    }
    equation.good_answer_id = rand()%4;
    equation.answers[equation.good_answer_id] = std::to_string(equation.good_answer);
}

void Board::write_equation(){
    if(progress < 100){
        messenger->write_blank(equation.equation,equation.rect.x,equation.rect.y);
        for(int x = 0; x < 4; x++){
            int w,h;
            messenger->write_box(equation.answers[x],equation.answers_rect.x + 80*x,equation.answers_rect.y,w,h);
            equation.width[x] = w;
            equation.height[x] = h;
        }
        messenger->write_blank("Progress... " + std::to_string(progress),equation.rect.x,equation.rect.y + 200);
    }else{
        messenger->write_blank("Board Complete...",equation.rect.x,equation.rect.y);
    }
}