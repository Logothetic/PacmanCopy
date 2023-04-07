#include "Tral.h"

using namespace std;

Tral::Tral(const char* c,char p):Moving(c,p){}


int Tral::find_path(vector<vector<char>> &map,int py,int px){
    if(py==posy && px==posx)
        return(stand);

    if(py==posy && px<posx){//same height and to the left
        if( possible(map[posy][posx-1]) )
            return(left);
        else if( possible(map[posy+1][posx]) )
            return(down);
        else if( possible(map[posy][posx+1]) )
            return(right);
        else
            return(up);
    }

    if(py==posy && px>posx){//same height and to the right
       if( possible(map[posy][posx+1]) )
            return(right);
        else if( possible(map[posy+1][posx]) )
            return(down);
        else if( possible(map[posy][posx-1]) )
            return(left);
        else
            return(up);
    }

    if(py<posy && px==posx){//same column and higher
        if( possible(map[posy-1][posx]) )
            return(up);
        else if( possible(map[posy][posx+1]) )
            return(right);
        else if( possible(map[posy][posx-1]) )
            return(left);
        else
            return(down);
    }

    if(py>posy && px==posx){//same column and lower
        if( possible(map[posy+1][posx]) )
            return(down);
        else if( possible(map[posy][posx+1]) )
            return(right);
        else if( possible(map[posy][posx-1]) )
            return(left);
        else
            return(up);
    }

    if(py>posy && px<posx){//down and to the left
        if( possible(map[posy+1][posx]) )
            return(down);
        else if( possible(map[posy][posx-1]) )
            return(left);
        else if( possible(map[posy-1][posx]) )
            return(up);
        else
            return(right);
    }

    if(py>posy && px>posx){//down and to the right
        if( possible(map[posy+1][posx]) )
            return(down);
        else if( possible(map[posy][posx+1]) )
            return(right);
        else if( possible(map[posy-1][posx]) )
            return(up);
        else
            return(left);
    }

    if(py<posy && px<posx){//up and to the left
        if( possible(map[posy-1][posx]) )
            return(up);
        else if( possible(map[posy][posx-1]) )
            return(left);
        else if( possible(map[posy+1][posx]) )
            return(down);
        else
            return(right);
    }

    if(py<posy && px>posx){//up and to the right
        if( possible(map[posy-1][posx]) )
            return(up);
        else if( possible(map[posy][posx+1]) )
            return(right);
        else if( possible(map[posy+1][posx]) )
            return(down);
        else
            return(left);
    }

    return 0;
}

bool Tral::possible(char c){
    if(c==' ' || c=='@')
        if(c!='G')
            return(true);
    return(false);
}
