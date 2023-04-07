#ifndef TRAL_H
#define TRAL_H

#include <iostream>
#include <vector>
#include "Moving.h"

using namespace std;

class Tral:public Moving{
    public:
        Tral(const char *,char);
        int find_path(vector<vector<char>> & ,int ,int);
        bool possible(char);
};
#endif
