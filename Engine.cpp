#include "Engine.h"

using namespace std;

Engine::Engine(Potter &po,Gnome &go,Tral & tl,Highscore & hs):p(po),g(go),t(tl),h(hs){
    keypad(stdscr,true);
}


void Engine::welcome_screen(){

    ifstream file("Welcome.txt");
    string line;

    init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
    attron(COLOR_PAIR(1));
    while(getline(file,line)){
        printw(line.c_str());
        printw("\n");
    }
    printw("Enter Your Name: ");
    refresh();
    enter_name();
    refresh();
    attroff(COLOR_PAIR(1));
    clear();
    noecho();
    curs_set(0);
    file.close();

    return;
}


void Engine::enter_name(){
    while(1){
        refresh();
        string s;
        cin>>s;
        if(strlen(s.c_str())<11){
            h.set_name(s);
            break;
        }
    }
    return;
}


void Engine::message_screen(string s){
    clear();
    ifstream file(s);
    string line;
    init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
    attron(COLOR_PAIR(1));
    while(getline(file,line)){
        printw(line.c_str());
        printw("\n");
    }
    refresh();
    attroff(COLOR_PAIR(1));
    getch();
    clear();
    file.close();

    return;
}


void Engine::make_map(char* name){
        string line;
        ifstream file(name);
        vector<char> temp;
        int rows=0;
        int columns=0;
        int flag=0;


        if( !(file.is_open( )) ){
            cout<<"FILE DOES NOT EXIST!"<<endl;
            return;
        }

        while( getline(file,line) ){
                rows++;
                flag=columns;
                columns=strlen(line.c_str());
                if(columns!=flag && rows!=1){
                    cout<<"NOT ALL ROWS HAVE THE SAME COLUMN SIZE!!"<<endl;
                    return;
                }else{
                    temp.clear();
                    for(int i=0;i<columns;i++)
                        temp.push_back(line[i]);
                    Map.push_back(temp);
                }
        }
    map_rows=rows;
    map_columns=columns;
    file.close();
    return;
}


void Engine::place_coins(){

    int r,c;
    srand(time(NULL));

    coins_map.resize(map_rows,vector<int>(map_columns,0));
    for(int i=0;i<10;i++){
        do{
            r=(rand()%(map_rows-1)+1);
            c=(rand()%(map_columns-1)+1);
        }while(Map[r][c]!=' ');
        coins_map[r][c]=1;
    }
    return;
}


void Engine::place_in_map(Moving& m){
    int r,c;
    do{
        r=(rand()%(map_rows-1)+1);
        c=(rand()%(map_columns-1)+1);
    }while(Map[r][c]!=' ');
    char ch;
    ch=m.get_ch();
    Map[r][c]=ch;
    m.set_pos(r,c);
    return;
}


void Engine::place_characters(){
    place_in_map(p);
    place_in_map(g);
    place_in_map(t);
}


void Engine::show_map(){
    refresh();
    init_color(COLOR_YELLOW,1000,1000,100);
    init_pair(gnome,COLOR_RED,COLOR_BLACK);
    init_pair(tral,COLOR_GREEN,COLOR_BLACK);
    init_pair(pacman,COLOR_YELLOW,COLOR_BLACK);
    init_pair(wall,COLOR_BLUE,COLOR_BLACK);
    init_pair(coins,COLOR_MAGENTA,COLOR_BLACK);

    for(int i=0;i<map_rows;i++){
        for(int j=0;j<map_columns;j++){
            move(i,j);
            if(coins_map[i][j]==1){
                attron(COLOR_PAIR(coins));
                printw("$");
                attroff(COLOR_PAIR(coins));
            }
            if(Map[i][j]==' ')
                printw(" ");
            else if(Map[i][j]=='*'){
                attron(A_REVERSE);
                attron(COLOR_PAIR(wall));
                printw(".");
                attroff(A_REVERSE);
                attroff(COLOR_PAIR(wall));
            }
            else if(Map[i][j]=='@'){
                attron(COLOR_PAIR(pacman));
                printw("@");
                attroff(COLOR_PAIR(pacman));
            }
            else if(Map[i][j]=='G'){
                attron(COLOR_PAIR(gnome));
                printw("G");
                attroff(COLOR_PAIR(gnome));
            }
            else if(Map[i][j]=='T'){
                attron(COLOR_PAIR(tral));
                printw("T");
                attroff(COLOR_PAIR(tral));
            }
        }
    }
    refresh();
    return;
}


void Engine::start_game(){
    bool flag=false;
    refresh();
    do{
        show_score();
        if(p.get_move(Map))
            return;
        g.get_move(Map,g.find_path(Map));
        t.get_move(Map,t.find_path(Map,p.get_y(),p.get_x()));
        p.display_move(pacman);
        g.display_move(gnome);
        t.display_move(tral);
        update_score();
        if(collision()==true){
            message_screen("GameOver.txt");
            break;
        }
        if(h.get_score()==100 && flag==false){
            place_last_coin();
            flag=true;
        }
        refresh_coins();
    }while(h.get_score()<200);
    if(h.get_score()==200)
        message_screen("YouWon.txt");
    return;
}


void Engine::show_score(){
    mvprintw(0,map_columns+2,"SCOREBOARD");
    for(int i=0;i<5;i++){
        mvprintw(i+1,map_columns+1,"%s %d",highscore_list[i].get_name(),highscore_list[i].get_score());
    }
    mvprintw(6,map_columns+1,"%s %d",h.get_name(),h.get_score());
    refresh();
    return;
}


void Engine::update_score(){
    int y=p.get_y();
    int x=p.get_x();
    if(coins_map[y][x]==1)
        get_coin(y,x);
    else if(coins_map[y][x]==2)
        h.set_score(200);
    return;
}


void Engine::get_coin(int y,int x){
    coins_map[y][x]=0;
    h++;
    return;
}


void Engine::refresh_coins(){
    for(int i=0;i<map_rows;i++){
        for(int j=0;j<map_columns;j++){
            if(coins_map[i][j]==1 && Map[i][j]==' '){
                init_pair(coins,COLOR_MAGENTA,COLOR_BLACK);
                attron(COLOR_PAIR(coins));
                mvaddch(i,j,'$');
                attroff(COLOR_PAIR(coins));
                refresh();
            }
            else if(coins_map[i][j]==2 && Map[i][j]==' '){
                init_pair(last_coin,COLOR_YELLOW,COLOR_BLACK);
                attron(COLOR_PAIR(last_coin));
                mvaddch(i,j,'*');
                attroff(COLOR_PAIR(last_coin));
                refresh();
            }
        }
    }
    return;
}


void Engine::place_last_coin(){
    int r,c;
    srand(time(NULL));
    do{
        r=(rand()%(map_rows-1)+1);
        c=(rand()%(map_columns-1)+1);
    }while(Map[r][c]!=' ');
    coins_map[r][c]=2;
    return;
}


bool Engine::collision(){
    if(p.get_y()==g.get_y() && p.get_x()==g.get_x())
        return true;
    if(p.get_y()==t.get_y() && p.get_x()==t.get_x())
        return true;
    return false;
}


void Engine::load_list(char* name){

    ifstream file(name);
    if( !(file.is_open( )) ){
        cout<<"FILE DOES NOT EXIST!"<<endl;
        return;
    }

    int temp_score[5];
    string temp_name[5];

    for(int i=0;i<5;i++)
        file>>temp_name[i]>>temp_score[i];

    for(int i=0;i<5;i++){
        highscore_list[i].set_name(temp_name[i]);
        highscore_list[i].set_score(temp_score[i]);
    }

//     delete temp_score;
//     delete temp_name;
    file.close();
    return;
}


void Engine::update_list(char* s){

    ofstream file;
    file.open(s,ios::out | ios::trunc);
    if(!file.is_open())
        exit(1);

    file.clear();
    int scr=h.get_score();
    for(int i=0;i<5;i++){
        if(scr>highscore_list[i].get_score()){
            for(int j=4;j>i;j--){
                highscore_list[j].set_name(highscore_list[j-1].get_name());
                highscore_list[j].set_score(highscore_list[j-1].get_score());
            }
            highscore_list[i].set_name(h.get_name());
            highscore_list[i].set_score(scr);
            break;
        }
    }
    for(int i=0;i<5;i++){
        file<<highscore_list[i].get_name()<<" ";
        file<<highscore_list[i].get_score()<<"\n";
    }

    file.close();
    return;
}
