#include "./Colors.h"

using namespace std;



namespace Colors{
    //Functions to get that colors will just return the additional string
    void RED(string data){
        cout << ("\033[" + to_string(pv_cols_term_nr::RED) + "m" + data);
    }

    void BLUE(string data){
        cout << ("\033[" + to_string(pv_cols_term_nr::BLUE) + "m" + data);
    }

    void YELLOW(string data){
        cout << ("\033[" + to_string(pv_cols_term_nr::YELLOW) + "m" + data);
    }

    void GREEN(string data){
        cout << ("\033[" + to_string(pv_cols_term_nr::GREEN) + "m" + data);
    }

    void WHITE(string data){
        cout << ("\033[" + to_string(pv_cols_term_nr::WHITE) + "m" + data);
    }

    void RESET(string data){
        cout << ("\033[" + to_string(pv_cols_term_nr::RESET) + "m" + data);
    }
}
