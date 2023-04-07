#include "Moving.h"

using namespace std;

Moving::Moving(const char *cc,char c){
    cch=cc;
    ch=c;
}


void Moving::set_pos(int y,int x){
    posy=y;
    posx=x;
}


int Moving::get_y(){ return posy; }


int Moving::get_x(){ return posx; }


char Moving::get_ch(){ return ch; }


bool Moving::get_move(vector<vector<char>> &m,int a){
    char temp;
    bool flag=0;
    if(a!=0){
        if(a==up){
            mvup(m);
            return false;
        }
        else if(a==down){
           mvdown(m);
           return false;
        }
        else if(a==left){
            mvleft(m);
            return false;
        }
        else if(a==right){
            mvright(m);
            return false;
        }
        else
            return false;
    }
    else{
        while(flag==0){
            while(1){
                temp=getch();
                if(temp==(char)KEY_UP || temp==(char)KEY_DOWN || temp==(char)KEY_LEFT || temp==(char)KEY_RIGHT || temp==' ')
                    break;
                if(temp==27)
                    return true;
            }
            switch(temp){
                case (char)KEY_UP:flag=mvup(m);break;
                case (char)KEY_DOWN:flag=mvdown(m);break;
                case (char)KEY_LEFT:flag=mvleft(m);break;
                case (char)KEY_RIGHT:flag=mvright(m);break;
                case ' ':flag=1;break;
            }
        }
    }
    if(temp==' ')
        return false;


    return false;
}

bool Moving::mvup(vector<vector<char>> &m){
    if(m[posy-1][posx]!='*'){
        mvaddch(posy,posx,' ');
        m[posy][posx]=' ';
        posy--;
        m[posy][posx]=ch;
        return(1);
    }
    return(0);
}

bool Moving::mvdown(vector<vector<char>> &m){
    if(m[posy+1][posx]!='*'){
        mvaddch(posy,posx,' ');
        m[posy][posx]=' ';
        posy++;
        m[posy][posx]=ch;
        return(1);
    }
    return(0);
}

bool Moving::mvleft(vector<vector<char>> &m){
    if(m[posy][posx-1]!='*'){
        mvaddch(posy,posx,' ');
        m[posy][posx]=' ';
        posx--;
        m[posy][posx]=ch;
        return(1);
    }
    return(0);
}

bool Moving::mvright(vector<vector<char>> &m){
    if(m[posy][posx+1]!='*'){
        mvaddch(posy,posx,' ');
        m[posy][posx]=' ';
        posx++;
        m[posy][posx]=ch;
        return(1);
    }
    return(0);
}

void Moving::display_move(int i){
    start_color();
    init_color(COLOR_YELLOW,1000,1000,100);
    init_pair(pacman,COLOR_YELLOW,COLOR_BLACK);
    init_pair(gnome,COLOR_RED,COLOR_BLACK);
    init_pair(tral,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(i));
    mvaddch(posy,posx,ch);
    attroff(COLOR_PAIR(i));
    refresh();
}
