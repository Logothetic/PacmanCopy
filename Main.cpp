#include <iostream>
#include "Engine.h"
#include "Moving.h"
#include "Gnome.h"
#include "Tral.h"
#include "Potter.h"


using namespace std;

int main(int argc ,char ** argv){

    initscr();
    refresh();
    start_color();

    Potter p("@",'@');
    Gnome g("G",'G');
    Tral t("T",'T');
    Highscore h;
    Engine a(p,g,t,h);

    a.load_list(argv[2]);
    a.welcome_screen();
    a.make_map(argv[1]);
    a.place_coins();
    a.place_characters();
    a.show_map();
    refresh();
    a.start_game();
    a.update_list(argv[2]);


    endwin();
    return 0;
}
