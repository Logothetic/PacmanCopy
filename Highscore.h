#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Highscore{
    private:
        char* name;
        int score;
    public:
        Highscore();
        void set_name(string);
        void set_score(int);
        char* get_name();
        int get_score();
        void operator++(int);
};
#endif
