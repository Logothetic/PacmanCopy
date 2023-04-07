#include "Highscore.h"

using namespace std;

Highscore::Highscore(){score=0;}

void Highscore::set_name(string s){
    name=new char [strlen(s.c_str())+1];
    strcpy(name,s.c_str());
    return;
}


int Highscore::get_score(){ return score; }

void Highscore::operator++(int){score=score+10;return;}

char* Highscore::get_name(){ return name; }

void Highscore::set_score(int s){ score=s;return;}
