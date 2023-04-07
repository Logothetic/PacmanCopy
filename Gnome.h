#ifndef GNOME_H
#define GNOME_H

#include <iostream>
#include <vector>
#include "Moving.h"

using namespace std;

class Gnome:public Moving{
    public:
        Gnome(const char*,char);
        void fill_path(int ,int,int ,int ,vector<vector<int>> & ,int);
        int find_path(vector<vector<char>>&);
        int get_random_move();
        void look_up(int ,int ,int ,int ,vector<vector<int>>  &,int );
        void look_down(int ,int ,int ,int ,vector<vector<int>>  &,int );
        void look_left(int ,int ,int ,int ,vector<vector<int>>  &,int );
        void look_right(int ,int ,int ,int ,vector<vector<int>>  &,int );
};
#endif
