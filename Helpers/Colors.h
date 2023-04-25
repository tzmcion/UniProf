#include <string>
#include <iostream>

using namespace std;


#ifndef COLORS_H
#define COLORS_H

namespace Colors{
    //Static class with numbers oid colors in terminal
    class pv_cols_term_nr{
        public:
            static const int RED = 91, BLUE=94, YELLOW=93, GREEN=92, WHITE=97, RESET=0;
    };
    //Functions to get that colors will just return the additional string

    void RED(string data);

    void BLUE(string data);

    void YELLOW(string data);

    void GREEN(string data);

    void WHITE(string data);

    void RESET(string data);
}

#endif