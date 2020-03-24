#include<iostream>
#include "./config.cpp"
#include <cmath>
#include<stdlib.h>
using namespace std;


//declaring signatures
void branch_menu();
void start_game();
void main_menu();

struct State {
    vector<vector<char>> main_array;
    bool curr_player;
    _location curr_pos;
    bool game_over;
};

State state;

void init(){
    setConsoleDimensions(WINDOW_SIZE.x, WINDOW_SIZE.y);
    setConsoleScrollBarVisibility(false);
    cursorVisAndSize(false);
    enableConsoleResize(false);
    setBgClr(BG_CLR, true);
}


char GetArrowKeysInput(){
    while(1)
    {
    switch(getch())
    {
    case 72:
        return 'U';
    case 80:
        return 'D';
    case 75:
        return 'L';
    case 77:
        return 'R';
    case 13:
        return 'E';
    case 27:
        return 'B';
    }
    }
}

void userInput(){
    cout << "\n\n     PRESS ENTER TO PLAY AGAIN AND PRESS ESCAPE TO GET TO MENU";
            char Input=GetArrowKeysInput();
            if(Input=='E')
                start_game();
            else if(Input=='B')
                main_menu();
}

void renderBoard(){



    for(int i=0; i<BOARD_SIZE+1 ; i++)
    {
        //horizontal line
        int lhy1 = START_POS.y - LINE_GAP.y/2 - (BOARD_SIZE/2 - i)*LINE_GAP.y - (BOARD_SIZE/2 + 1 - i)*BOARD_LINE_THICKNESS.y;
        int lhy2 = lhy1 + BOARD_LINE_THICKNESS.y;
        int lhx1 = START_POS.x - LINE_GAP.x/2 - (BOARD_SIZE/2)*LINE_GAP.x - (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.x;
        int lhx2 = START_POS.x + LINE_GAP.x/2 + (BOARD_SIZE/2)*LINE_GAP.x + (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.x;
        clrdLine(BOARD_CLR, lhx1, lhy1, lhx2, lhy2);

        //vertical line
        int lvy1 = START_POS.y - LINE_GAP.y/2 - (BOARD_SIZE/2)*LINE_GAP.y - (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.y;
        int lvy2 = START_POS.y + ceil(LINE_GAP.y/2.0) + (BOARD_SIZE/2)*LINE_GAP.y + (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.y;
        int lvx1 = START_POS.x - LINE_GAP.x/2 - (BOARD_SIZE/2 - i)*LINE_GAP.x - (BOARD_SIZE/2 + 1 - i)*BOARD_LINE_THICKNESS.x;
        int lvx2 = lvx1 + BOARD_LINE_THICKNESS.x;
        clrdLine(BOARD_CLR, lvx1, lvy1, lvx2, lvy2);


}
}

void printMarkerOnBoard(char marker, int x, int y){
    int factor = BOARD_SIZE/2;
    _location offset = {LINE_GAP.x + BOARD_LINE_THICKNESS.x, LINE_GAP.y + BOARD_LINE_THICKNESS.y};
    _location start = {START_POS.x - factor*offset.x, START_POS.y - factor*offset.y};

    Locate(start.x + x*offset.x, start.y + y*offset.y);
    cout << marker;
}

void stateArray2Board(){
    for(int r=0; r<BOARD_SIZE; ++r){
        for(int c=0; c<BOARD_SIZE; ++c){
            printMarkerOnBoard(state.main_array[r][c], c, r);
        }
    }
}

char getCurrMarker(bool currPlayer){
    if(currPlayer==0)
    {
        return PLAYER_1_MARKER;
    }
    else return PLAYER_2_MARKER;
}

void gameLogic(int row=BOARD_SIZE, int col=BOARD_SIZE){
    bool isDrawn = true;

    //for rows
    for(int r=0; r<row; ++r){
        char firstMarker = state.main_array[r][0];
        int hCounter = 0;
        for(int c=0; c<col; ++c){
            if(state.main_array[r][c] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][c]) break;
            else hCounter++;
        }
        if(hCounter == col){
            if(BOARD_SIZE==9)
            {
            Locate(5,40);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !";
            userInput();
            }
            else
            {
            Locate(5,35);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !" ;
            userInput();
            }
    }
    }

    //for cols
    for(int c=0; c<col; ++c){
        char firstMarker = state.main_array[0][c];
        int vCounter = 0;
        for(int r=0; r<row; ++r){
            if(state.main_array[r][c] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][c]) break;
            else vCounter++;
        }
        if(vCounter == row){
            if(BOARD_SIZE==9)
            {
            Locate(5,40);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !";
            userInput();
            }
            else
            {
            Locate(5,35);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !" ;
            userInput();
            }



    firstMarker = state.main_array[1][1];
    }
     //for left diagonal
     int ldCounter = 0;
     for(int r=0; r<row; ++r){
        if(state.main_array[r][r] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][r]) break;
            else ldCounter++;
     }
     if(ldCounter == row){
            if(BOARD_SIZE==9)
            {
            Locate(5,40);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !";
            userInput();
            }
            else
            {
            Locate(5,35);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !" ;
            userInput();
            }
    }

    //for right diagonal
    int rdCounter = 0;
     for(int r=0; r<row; ++r){
        if(state.main_array[r][row-r-1] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][row-r-1]) break;
            else rdCounter++;
     }
     if(rdCounter == row){
            if(BOARD_SIZE==9)
            {
            Locate(5,40);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !";
            userInput();
            }
            else
            {
            Locate(5,35);
            cout << "PLAYER WITH MARKER " << firstMarker << " WINS !" ;
            userInput();
            }
        }

    //check draw condition
    if(isDrawn){
        if(BOARD_SIZE==9)
            {
            Locate(5,40);
            cout << "MATCH IS DRAWN";
            userInput();
            }
            else
            {
            Locate(5,35);
            cout << "MATCH IS DRAWN";
            userInput();
            }
    }

    state.curr_player= !state.curr_player;
}
}

void show_current_player(){

    if(state.curr_player==0){
          Locate(2,3);
          cout<<"PLAYER 1";
          }
          else{
              Locate(2,3);
          cout<<"PLAYER 2";
          }
}

void getUserMove(){
    char Input=GetArrowKeysInput();
    if(Input=='U' && state.curr_pos.y > 0)
        state.curr_pos.y--;
    else if(Input=='D' && state.curr_pos.y < BOARD_SIZE-1)
        state.curr_pos.y++;
    else if(Input=='L' && state.curr_pos.x > 0)
        state.curr_pos.x--;
    else if(Input=='R' && state.curr_pos.x < BOARD_SIZE-1)
        state.curr_pos.x++;
    else if(Input=='E') {

        if(state.main_array[state.curr_pos.y][state.curr_pos.x] == EMPTY_MARKER){
            state.main_array[state.curr_pos.y][state.curr_pos.x] = getCurrMarker(state.curr_player);
             gameLogic();
        }
    }
}

void start_game(){
    system("cls");

    //set initial state
   //fill_array(state.main_array, EMPTY_MARKER);
   state.main_array = vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE,EMPTY_MARKER));
    state.curr_player = 0;
    state.curr_pos = {0, 0};
    state.game_over = false;

    //render board
    renderBoard();


    //play game
    while(state.game_over == false)
    {
        stateArray2Board();
        printMarkerOnBoard(getCurrMarker(state.curr_player), state.curr_pos.x, state.curr_pos.y);
        getUserMove();
        show_current_player();
    }

    system("cls");
}

void board_size(){
    system("cls");
    Menu boardSize({"3x3","5x5","7x7","9x9","BACK"});
    boardSize.setHeading("SELECT BOARD SIZE");
    int selectedSize = boardSize.drawMenu();
    switch(selectedSize){
        case 1:
            BOARD_SIZE=3;
            break;
        case 2:
            BOARD_SIZE=5;
            break;
        case 3:
            BOARD_SIZE=7;
            break;
        case 4:
            BOARD_SIZE=9;
            break;
        case 5:
            break;
            }
    }

void chnge_bg_color(){

    system("cls");
    Menu bg_color({"Red","Green","Yellow"});
    switch(bg_color.drawMenu()){
    case 1:
        BG_CLR = "Red";
        setBgClr(BG_CLR,1);
        break;
    case 2:
        BG_CLR = "Green";
        setBgClr(BG_CLR,1);
        break;
    case 3:
        BG_CLR = "Yellow";
        setBgClr(BG_CLR,1);
        break;
    }
}

void chnge_bord_color(){

    system("cls");
    Menu brd_color({"Black","Red","L Blue"});
    switch(brd_color.drawMenu()){
    case 1:
        BOARD_CLR="Black";
        break;
    case 2:
        BOARD_CLR="Red";
        break;
    case 3:
        BOARD_CLR="Blue";
        break;

}
}

void branch_colour(){

    system("cls");
    Menu subBranch({"Back Ground Colour","Border Colour","Board Back Ground Colour"});
    switch(subBranch.drawMenu()){
    case 1:
        chnge_bg_color();
        break;
    case 2:
        chnge_bord_color();
        break;
    case 3:
        break;

}
}

void Custom_marker(){

    system("cls");
    char mark1,mark2;
    cout<<"Select Player 1 Marker  ";
    cin>>mark1;
    PLAYER_1_MARKER=mark1;
    cout<<"Select Player 2 Marker ";
    cin>>mark2;
    PLAYER_2_MARKER=mark2;
}

void branch_menu(){

    system("cls");
    Menu branchMenu({"Board size","Colour","Player mark"});
    switch(branchMenu.drawMenu()){
    case 1:
        board_size();
        break;
    case 2:
        branch_colour();
        break;
    case 3:
        Custom_marker();
        break;

    }
}

void main_menu(){

    Menu _mainMenu({"2 players","Cpu vs player","setting","Exit"});
    system("cls");
    switch(_mainMenu.drawMenu()){
    case 1:
        start_game();
        break;
    case 2:
        break;
    case 3:
        branch_menu();
        main_menu();
        break;
    case 4:
        break;
    }
}



int main()
{
    init();
    main_menu();
    Locate(50,50);
    return 0;
}
