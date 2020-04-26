#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int poor(const vector < vector<char> > &, char, char);
//void checkPosition(char, char, vector < vector<char> >, vector<int> &);
bool willWinT(char, int, vector < vector<char> >, vector<int>);
int scoreT(char, int, vector < vector<char> >, vector<int>);


int poor(const vector < vector<char> > &board, char mydisc, char yourdisc) {
    static const char me = mydisc; //Record the disc type main function assigns for this AI. It never changes once assigned
    static const char opponent = yourdisc; //Record the disc type main function assigns for another AI. It never changes once assigned
    int column = -1;
    //Write a simple AI for testing
    
    
    
    //∂√æ∫ÿ§l
    srand((unsigned)time(NULL));
    
    //´≈ßi
    int posScore[7] = {};//¶s®C§@¶Ê™∫™≈¶Ï™∫§¿º∆
    vector<int> position(7, 5);//¶s®C§@¶Ê™∫™≈¶Ï¶Ï∏m,™Ï©l§∆position¨“¨∞5
    
    //ß‰®C§@¶Ê™∫™≈¶Ï¶Ï∏m
    checkPosition(me, opponent, board, position);
    
    //∫‚≤ƒ¥X¶^
    int turn = 1;//¶π¶^™∫¶^º∆
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] != 0) {//¶≥¥X≠”ΩL§l¥N•N™ÌπL§F¥X¶^
                turn++;
            }
        }
    }
    
    //ßP¬_¶€§v¨O•˝§‚¡Ÿ¨O´·§‚
    //•H§U¨∞•Œ©Û´e®‚¶^™∫µ¶≤§
    
    //•˝§‚
    //≤ƒ§@®B°B≤ƒ§G®B≥£©Ò§§∂°
    if (turn == 1 || turn == 3) {
        return 3;
    }
    //´·§‚
    //≤ƒ§@®B©Ò§§∂°
    else if (turn == 2) {
        return 3;
    }
    //≤ƒ§G®B
    else if (turn == 4) {
        //≠YπÔ§‚©Ò§§∂°°A¶€§v§]©Ò§§∂°
        if (position[3] == 2) {
            return 3;
        }
        //≠YπÔ§‚©Ò§§∂°™∫•™(2)©Œ•k(4)¶Ê°A´h©Ò¨€§œ√‰°F≠YπÔ§‚©Ò®‰•L¶Ê°A´h©Ò2or4(≥£§@ºÀ)
        if (position[2] == 4) {//πÔ§‚©Ò2
            return 4;//¶€§v©Ò4
        }
        else if (position[4] == 4) {//πÔ§‚©Ò4
            return 2;//¶€§v©Ò2
        }
        else {//ß_´h©Ò2or4
            if (rand() % 2 == 0) {
                return 2;
            }
            else {
                return 4;
            }
        }
    }
    
    
    //•H§U¨∞≥—§U¶^º∆™∫µ¶≤§
    
    //≠¢§‚ßP¬_°]≠¢§‚°G§U§@≠”©Ò§U•h¥Nƒπ§F°^°G•˝ßP¬_¶€§v™∫°A¶€§v®S¶≥¶AßP¬_πÔ§‚™∫
    //ßP¬_¶€§v¶b¶U¶Ê™≈¶Ï¨Oß_¶≥≠¢§‚°A¶≥¥N©Ò∏”¶Ê°Aƒπ±oπC¿∏
    for (int i = 6; i >= 0; i--) {
        if (willWinT(me, i, board, position)) {
            return i;
        }
    }
    //ßP¬_πÔ§‚¶b¶U¶Ê™≈¶Ï¨Oß_¶≥≠¢§‚°A¶≥¥N©Ò∏”¶Ê°A™˝§ÓπÔ§‚
    for (int i = 6; i >= 0; i--) {
        if (willWinT(opponent, i, board, position)) {
            return i;
        }
    }
    
    //≠p∫‚¶U¶Ê™≈¶Ï§¿º∆
    for (int i = 0; i < 7; i++) {
        if (position[i] <= 0) {//∫°§FßO¶A©Ò°A©“•Hß‚§¿º∆≥]´‹ßC
            posScore[i] = -100;
        }
        else {
            posScore[i] = scoreT(me, i, board, position);
        }
    }
    
    //øÔ¶U¶Ê™≈¶Ï§§§¿º∆≥Ã∞™™∫
    int highest = 0;
    for (int i = 1; i<7; i++) {
        if (posScore[i] > posScore[highest]) {
            highest = i;
        }
        /*else if (posScore[i] == posScore[highest]) {
            if (rand() % 2 == 0) {
                highest = i;
            }
            else {
                continue;
            }
        }*/
    }
    column = highest;
    
    
    
    //Write your AI here
    
    return column;
}


//ß‰®C§@¶Ê™∫™≈¶Ï¶Ï∏m
/*void checkPosition(char mydisc, char yourdisc, vector< vector<char> > board, vector<int> &position) {
 
 for (int j = 0; j < 7; j++) {
 for (int i = 5; i >= 0; i--) {//•—§U©π§Wß‰
 if (board[i][j] == mydisc || board[i][j] == yourdisc) {
 position[j]--;//¶≥ΩL§l¥Nß‚™≈¶Ï¶Ï∏m©π§W¥£
 }
 else {
 break;
 }
 }
 }
 
 }*/

//≠p¶U¶Ê™≈¶Ï§¿º∆°A§Z¶≥¶b¶€§vΩL§l™∫≥sΩu§W¥N+1§¿
int scoreT(char mydisc, int column, vector< vector<char> > board, vector<int> position) {
    
    int row = position[column];//¶π¶Ê™≈¶Ï¶b≤ƒ¥X¶C
    int own = 0;//¨ˆø˝™≈¶Ï™˛™Ò¨O¶€§v™∫≥sƒÚ¶≥¥X≠”
    int empty = 0;//¨ˆø˝™≈¶Ï™˛™Ò¨O™≈™∫≥sƒÚ¶≥¥X≠”
    int score = 0;
    
    //π]™Ω
    //•—§W©π§Uß‰
    for (int y = 0; y < 6; y++) {
        if (board[y][column] == 0) {
            empty++;
        }
        else if (board[y][column] == mydisc) {
            own++;
        }
        else {
            break;//πJ®ÏπÔ§‚™∫ΩL§l->§£≥sƒÚ
        }
    }
    if ((own > 0) && ((own + empty) >= 4)) {//¶‹§÷≥sƒÚ•|≠”§~¶≥•Œ
        score += own;
    }
    
    //§Ù•≠©MπÔ®§Ωu
    for (int dy = -1; dy <= 1; dy++) {//dy=-1¨O©π§Uß‰°A=0¨O§Ù•≠ß‰°A=1¨O©π§Wß‰
        //•˝•™§U©π•k§W/°A¶A§Ù•≠-°A¶A•k§U©π•™§W\.
        own = 0;
        empty = 0;
        for (int dx = -1; dx <= 1; dx++) {//dx=-1¨O©π•™ß‰,=1¨O©π•kß‰, =0¨O¶€§v
            if (dx == 0) {//¶€§v
                empty++;//™≈ÆÊ+1
                continue;//ƒ~ƒÚ©π•kß‰
            }
            for (int x = column + dx, y = row + dx*dy; x < 7 && x >= 0 && y < 6 && y >= 0; x += dx, y += dx*dy) {
                if (board[y][x] == 0) {
                    empty++;
                }
                else if (board[y][x] == mydisc) {
                    own++;
                }
                else {
                    break;//πJ®ÏπÔ§‚™∫ΩL§lÆ…∞±§Ó°AßÔ∫‚•t§@√‰
                }
            }
        }
        if ((own > 0) && ((own + empty) >= 4)) {//¶‹§÷≥sƒÚ•|≠”§~¶≥•Œ
            score += own;
        }
    }
    return score;
}

//¿À¨d©Ò¶π¶Ê¨Oß_∑|ƒπ
bool willWinT(char mydisc, int column, vector< vector<char> > board, vector<int> position) {
    
    int row = position[column];
    if (row <= 0) {//∫°§FßO¶A©Ò
        return false;
    }
    //π]™Ω
    if (row < 3) {//©π§Uß‰
        if ((board[row + 1][column] == mydisc) && (board[row + 2][column] == mydisc) && (board[row + 3][column] == mydisc)) {
            return true;
        }
    }
    for (int dy = -1; dy <= 1; dy++) {//dy=-1¨O©π§Uß‰°A=0¨O§Ù•≠ß‰°A=1¨O©π§Wß‰
        //•˝•™§U©π•k§W°A¶A§Ù•≠°A¶A•k§U©π•™§W
        int own = 0;
        for (int dx = -1; dx <= 1; dx += 2) {//dx=-1¨O©π•™ß‰,=1¨O©π•kß‰,=0¨O¶€§v©“•H∏ıπL¶€§v≥o§@ÆÊ
            for (int x = column + dx, y = row + dx*dy; x < 7 && x >= 0 && y < 6 && y >= 0; x += dx, y += dx*dy) {
                if (board[y][x] == mydisc) {
                    own++;
                }
                else {
                    break;//πJ®ÏπÔ§‚™∫ΩL§lÆ…∞±§Ó°AßÔ∫‚•t§@√‰
                }
            }
        }
        if (own >= 3) {//¶‹§÷≥sƒÚ§T≠”°A©Ò§W¶€§v™∫§ß´·§~∑|≥”ßQ
            return true;
        }
    }
    return false;
}

