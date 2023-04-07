#include "Gnome.h"

using namespace std;

Gnome::Gnome(const char* c,char p):Moving(c,p){}


int Gnome::find_path(vector<vector<char>> &m){

    vector<vector<int>> map_copy;
    vector<int> temporary;

    int py,px;
    int rows=m.size();
    int columns=m[0].size();

    for(int i=0;i<rows;i++){
        temporary.clear();
        for(int j=0;j<columns;j++){
            if(m[i][j]=='*' || m[i][j]=='T')
                temporary.push_back(1000);
            else if(m[i][j]=='@'){
                py=i;
                px=j;
                temporary.push_back(999);
            }
            else if(m[i][j]==' ')
                temporary.push_back(0);
        }
        map_copy.push_back(temporary);
    }



    fill_path(py,px,posy,posx,map_copy,1);
    int S,A,B,L,R;
    S=map_copy[posy][posx];
    A=map_copy[posy-1][posx];
    B=map_copy[posy+1][posx];
    L=map_copy[posy][posx-1];
    R=map_copy[posy][posx+1];

    map_copy.clear();
    temporary.clear();

    if(S==999)
        return stand;
    if(A==999)
        return up;
    if(B==999)
        return down;
    if(L==999)
        return left;
    if(R==999)
        return right;

    if(A<=B && A<=L && A<=R && A!=0)
        return up;
    else if(B<=A && B<=L && B<=R && B!=0)
        return down;
    else if(L<=B && L<=A && L<=R && L!=0)
        return left;
    else if(R<=B && R<=L && R<=A && R!=0)
        return right;


    int r=get_random_move();
    if(r==1)
        if(A!=1000 || A!=0)
            return r;
    if(r==2)
        if(B!=1000 || B!=0)
            return r;
    if(r==3)
        if(L!=1000 || L!=0)
            return r;
    if(r==4)
        if(R!=1000 || R!=0)
            return r;

        return 0;
}


int Gnome::get_random_move(){
    srand(time(NULL));
    int temp=(rand() % 4)+1;
    return temp;
}

void Gnome::fill_path(int py,int px,int gy,int gx,vector<vector<int>>  &map,int i){
     if(gy==py && gx>=px){
        look_right(py,px,gy,gx,map,i);
        look_up(py,px,gy,gx,map,i);
        look_down(py,px,gy,gx,map,i);
        look_left(py,px,gy,gx,map,i);
    }
    if(gy==py && gx<=px){
        look_left(py,px,gy,gx,map,i);
        look_up(py,px,gy,gx,map,i);
        look_down(py,px,gy,gx,map,i);
        look_right(py,px,gy,gx,map,i);
    }
    if(gy>=py && gx==px){
        look_down(py,px,gy,gx,map,i);
        look_left(py,px,gy,gx,map,i);
        look_right(py,px,gy,gx,map,i);
        look_up(py,px,gy,gx,map,i);
    }
    if(gy<=py && gx==px){
        look_up(py,px,gy,gx,map,i);
        look_left(py,px,gy,gx,map,i);
        look_right(py,px,gy,gx,map,i);
        look_down(py,px,gy,gx,map,i);

    }
    if(gy>py && gx>px){
        look_down(py,px,gy,gx,map,i);
        look_right(py,px,gy,gx,map,i);
        look_up(py,px,gy,gx,map,i);
        look_left(py,px,gy,gx,map,i);
    }
    if(gy<py && gx>px){
        look_up(py,px,gy,gx,map,i);
        look_right(py,px,gy,gx,map,i);
        look_down(py,px,gy,gx,map,i);
        look_left(py,px,gy,gx,map,i);
    }
    if(gy<py && gx<px){
        look_up(py,px,gy,gx,map,i);
        look_left(py,px,gy,gx,map,i);
        look_down(py,px,gy,gx,map,i);
        look_right(py,px,gy,gx,map,i);
    }
    if(gy>py && gx<px){
        look_down(py,px,gy,gx,map,i);
        look_left(py,px,gy,gx,map,i);
        look_up(py,px,gy,gx,map,i);
        look_right(py,px,gy,gx,map,i);
    }
    return;
}



void Gnome::look_up(int py,int px,int gy,int gx,vector<vector<int>>  &map,int i){
    if(map[py-1][px]==0){
        map[py-1][px]=i;
        fill_path(py-1,px,gy,gx,map,i+1);
    }
    return;
}

void Gnome::look_down(int py,int px,int gy,int gx,vector<vector<int>>  &map,int i){
     if(map[py+1][px]==0){
        map[py+1][px]=i;
        fill_path(py+1,px,gy,gx,map,i+1);
    }
    return;
}


void Gnome::look_left(int py,int px,int gy,int gx,vector<vector<int>>  &map,int i){
      if(map[py][px-1]==0){
        map[py][px-1]=i;
        fill_path(py,px-1,gy,gx,map,i+1);
    }
    return;
}


void Gnome::look_right(int py,int px,int gy,int gx,vector<vector<int>>  &map,int i){
    if(map[py][px+1]==0){
        map[py][px+1]=i;
        fill_path(py,px+1,gy,gx,map,i+1);
    }
    return;
}
