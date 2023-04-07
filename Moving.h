#ifndef MOVING_H
#define MOVING_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#define pacman 3
#define gnome  4
#define tral   5
#define up    1
#define down  2
#define left  3
#define right 4
#define stand 5

using namespace std;

class Moving{
        protected:
                int posx;
                int posy;
                char ch;
                const char * cch;
        public:
                Moving(const char *,char);
                void set_pos(int , int);
                int get_y();
                int get_x();
                char get_ch();
                void display_move(int i);
                bool get_move(vector<vector<char>> &m,int a=0);
                bool mvup(vector<vector<char>> &);
                bool mvdown(vector<vector<char>> &);
                bool mvleft(vector<vector<char>> &);
                bool mvright(vector<vector<char>> &);

};
#endif
