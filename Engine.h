#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include "Moving.h"
#include "Potter.h"
#include "Tral.h"
#include "Gnome.h"
#include "Highscore.h"
#define wall 1
#define coins 2
#define pacman 3
#define gnome 4
#define tral 5
#define last_coin 6


using namespace std;

class Engine{
    private:
        vector<vector<char>> Map;
        vector<vector<int>> coins_map;
        int map_rows;
        int map_columns;
        Highscore highscore_list[5];
        Highscore h;
        Potter p;
        Gnome g;
        Tral t;
    public:
        Engine(Potter &,Gnome &,Tral &,Highscore &);
        void welcome_screen();
        void enter_name();
        void message_screen(string s);
        void make_map(char *);
        void place_coins();
        void place_in_map(Moving&);
        void place_characters();
        void show_map();
        void start_game();
        void show_score();
        void update_score();
        void get_coin(int,int);
        void refresh_coins();
        void place_last_coin();
        bool collision();
        void load_list(char *);
        void update_list(char *);
};
#endif
