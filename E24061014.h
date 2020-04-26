#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//function prototype
int E24061014(const vector < vector<char> > &, char, char);
void checkPosition(char, char, vector < vector<char> >, vector<int> &);
bool willWin(char, int, vector < vector<char> >, vector<int>);
int score(char, int, vector < vector<char> >, vector<int>);
int trap(char, int[], vector < vector<char> >, vector<int>);

int E24061014(const vector < vector<char> > &board, char mydisc, char yourdisc) {
    static const char me = mydisc; //Record the disc type main function assigns for this AI. It never changes once assigned
    static const char opponent = yourdisc; //Record the disc type main function assigns for another AI. It never changes once assigned
    int column = -1;
    //Write your AI here
    srand((unsigned)time(NULL));
    //宣告
    int posScore[7] = {};//存每一行的空位的分數
    vector<int> position(7);//存每一行的空位位置
    
    //初始化position皆為5
    for(int i=0; i<7; i++){
        position.at(i) = 5;
    }
    
    //找每一行的空位位置
    checkPosition(me, opponent, board, position);
    
    //算第幾回
    int turn=1;//此回的回數
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            if(board[i][j]!=0){//有幾個盤子就代表過了幾回
                turn++;
            }
        }
    }
    //判斷自己是先手還是後手
    //以下為用於前兩回的策略
    if(turn%2==1){
        //先手
        //第一步、第二步都放中間
        if(turn==1 || turn==3){
            return 3;
        }
    }
    else{
        //後手
        //第一步放中間
        if(turn==2){
            return 3;
        }
        //第二步
        if(turn==4){
            //若對手放中間，自己也放中間
            if(position[3]==2){
                return 3;
            }
            //若對手放中間的左(2)或右(4)行，則放相反邊；若對手放其他行，則放2(2or4都一樣)
            if(position[2]==4){//對手放2
                return 4;//自己放4
            }
            else if(position[4]==4){//對手放4
                return 2;//自己放2
            }
            else{//否則4,2亂數擇一
                int x = rand()%2;
                if(x==0){
                    return 2;
                }
            }
        }
    }
    
    //以下為剩下回數的策略
    
    //計算各行空位分數
    for(int i=0; i<7; i++){
        if(position[i]<=0){//滿了別再放，所以把分數設很低
            posScore[i] = -10000000;
        }
        else{
            posScore[i] = score(me, i, board, position);
        }
        //cout << "score "<<i<<":"<<posScore[i] << endl;
    }
    //cout << endl;
    //迫手判斷（迫手：下一個放下去就贏了）：先判斷自己的，自己沒有再判斷對手的
    //判斷自己在各行空位是否有迫手，有就放該行，贏得遊戲
    for(int i=0; i<7; i++){
        if(willWin(me, i, board, position)){
            //cout <<"I will win at "<<i<<"\n";
            return i;
        }
    }
    //判斷對手在各行空位是否有迫手，有就放該行，阻止對手
    for(int i=0; i<7; i++){
        if(willWin(opponent, i, board, position)){
            //cout <<"HE will at "<<i<<"\n";
            return i;
        }
    }
   
    //若兩人都沒迫手，判斷是否能設雙空陷阱：先看自己，再看對手
    //（雙空：__oo__此時放o的左邊或右邊都可以形成陷阱 如放左邊：_ooo__，下一回無論對手放左還右，都擋不了）
    //判斷自己是否有雙空陷阱，有就設陷阱
    int setTrap;//要設陷阱的行數，若為-1表沒有雙空
    for(int i=0; i<7; i++){
        setTrap = trap(me, posScore, board, position);
        if(setTrap != -1){//有雙空
            //cout <<"I set trap at "<<i<<"\n";
            return setTrap;//設陷阱
        }
    }
    //判斷對手是否有雙空陷阱，有就阻擋
    for(int i=0; i<7; i++){
        setTrap = trap(opponent, posScore, board, position);
        if(setTrap != -1){//有雙空
            //cout <<"I block at "<<i<<"\n";
            return setTrap;//阻擋
        }
    }
    
    //兩人都沒有雙空
    //選各行空位中分數最高的
    int highest = 0;
    for(int i=1; i<7; i++){
        if(posScore[i] > posScore[highest]){
            highest = i;
        }
        else if(posScore[i] == posScore[highest]){
            int x = rand()%2;
            if(x == 0){
                highest = i;
            }
        }
    }
    column = highest;
    //cout << "I put "<< column<<endl;
    //Write your AI here
    
    return column;
}

//找每一行的空位位置
void checkPosition(char mydisc, char yourdisc, vector< vector<char> > board, vector<int> &position) {
    //cout <<"check";
    for(int j=0; j<7; j++){
        //cout << " "<<j;
        for(int i=5; i>=0; i--){//由下往上找
            //cout << " "<<i<<":";
            if(board[i][j]==mydisc||board[i][j]==yourdisc){
                //cout << board[i][j]<<endl;
                position[j]--;//有盤子就把空位位置往上提
                //cout << "position["<<j<<"]-1="<<position[j]<<endl;
            }
            else{
                //cout << board[i][j]<<" is empty"<<endl;
                break;
            }
        }
    }
    
}

//計各行空位分數，凡有在自己盤子的連線上就+1分
int score(char mydisc, int column, vector< vector<char> > board, vector<int> position){
    
    int row = position[column];//此行空位在第幾列
    int own = 0;//紀錄空位附近是自己的連續有幾個
    int empty = 0;//紀錄空位附近是空的連續有幾個
    int score = 0;
    
    //鉛直
    //由上往下找
    for(int y=0; y<6; y++){
        if(board[y][column] == 0){
            //cout << y<<','<<column<<" is empty"<<endl;
            empty++;
            //cout << "empty="<<empty<<endl;
        }
        else if(board[y][column] == mydisc){
            //cout << y<<','<<column<<" is own"<<endl;
            own++;
            //cout << "own="<<own<<endl;
        }
        else{
            break;//遇到對手的盤子->不連續
        }
    }
    //cout << "own="<<own<<endl;
    if( (own>0)&& ((own+empty) >= 4)){//至少連續四個才有用
        score += own;
        //cout << "vertical:"<<score<<endl;
    }
    
    //水平和對角線
    for(int dy=-1; dy<=1; dy++){//dy=-1是往下找，=0是水平找，=1是往上找
        //先左下往右上，再水平，再右下往左上
        own = 0;
        empty = 0;
        for(int dx=-1; dx<=1; dx++){//dx=-1是往左找,=1是往右找, =0是自己
            if(dx==0){//自己
                empty++;//空格+1
                continue;//繼續往右找
            }
            for(int x=column+dx, y=row+dx*dy; x<7 && x>=0 && y<6 && y>=0; x+=dx, y+=dx*dy){
                if(board[y][x] == 0){
                    empty++;
                }
                else if(board[y][x] == mydisc){
                    own++;
                }
                else{
                    break;//遇到對手的盤子時停止，改算另一邊
                }
            }
        }
        if( (own>0)&& ((own+empty) >= 4)){//至少連續四個才有用
            score += own;
        }
    }
   
    return score;
}

//檢查放此行是否會贏
bool willWin(char mydisc, int column, vector< vector<char> > board, vector<int> position){
    
    int row = position[column];
    //cout << column << "position is "<< row << "\n";
    if(row<=0){//滿了別再放
        //cout << row << " is full\n";
        return false;
    }
    //cout << "CHECK WILL WIN"<<i<<','<<j<<" "<<mydisc<<"\n";
    //鉛直
    if(row<3){//往下找
        if((board[row+1][column]==mydisc)&&(board[row+2][column]==mydisc)&&(board[row+3][column]==mydisc)){
            return true;
        }
    }
    for(int dy=-1; dy<=1; dy++){//dy=-1是往下找，=0是水平找，=1是往上找
        //先左下往右上，再水平，再右下往左上
        int own = 0;
        for(int dx=-1; dx<=1; dx+=2){//dx=-1是往左找,=1是往右找,=0是自己所以跳過自己這一格
            for(int x=column+dx, y=row+dx*dy; x<7 && x>=0 && y<6 && y>=0; x+=dx, y+=dx*dy){
                if(board[y][x] == mydisc){
                    own++;
                }
                else{
                    break;//遇到對手的盤子時停止，改算另一邊
                }
            }
        }
        if(own >= 3){//至少連續三個，放上自己的之後才會勝利
            return true;
        }
    }
    return false;
}

//檢查雙空陷阱
int trap(char player, int posScore[], vector< vector<char> > board, vector<int> position){
    
    int trap = -1;//預設-1表沒辦法設陷阱
    vector<int> subPosition2(4);
    vector<int> subPosition(5);//複製position的中間五個
    vector<int> pretrap = {1,1,2,4,5};//斜的長這樣有可能是雙空
    vector<int> pretrap2 = {5,3,3,5};//水平的長這樣或各減1可能是雙空，共五種
    //水平('低'代表>=隔壁)
    //case1:{低,5,3,3,5,低,?}
    //case2:{?,低,5,3,3,5,低}
    for(int x=0; x<=1; x++){//x=0是case1,=1是case2
        std::copy(position.begin()+x+1, position.begin()+x+4, subPosition2.begin());
        for(int i=0; i<4; i++){
            
            for(int j=0; j<4; j++){//更換可能情形
                pretrap2[j] -= i;
            }
            
            if(subPosition2 == pretrap2){
                if((board[position[2+x]+1][2+x] != player)||(board[position[3+x]+1][3+x] != player)){//兩個中間的(2+x,3+x)空位下面一格不是自己
                    continue;//沒水平陷阱
                }
                if((position[0+x] >= position[1+x])&&(position[5+x] >= position[4+x])){//最外行不能比最外第二行高
                    if(posScore[1+x] > posScore[4+x]){
                        return 1+x;
                    }
                    else{
                        return 4+x;
                    }
                }
            }
        }
    }
    
    
    //斜的有四種情形：('可'代表>=0)
    //左上右下
    //case1:{可,1,1,2,4,5,?}
    //case2:{?,可,1,1,2,4,5}
    for(int i=0; i<=1; i++){//i=0->case1,i=1-<case2
        //case2的數字都是case1+1
        std::copy(position.begin()+i+1, position.begin()+i+1+5, subPosition.begin());
        if(subPosition==pretrap){
            if((board[position[2+i]+1][2+i] != player)||(board[position[3+i]+1][3+i] != player)){//兩個中間的(2+i,3+i)空位往下一格不是自己
                continue;//沒事
            }
            if(position[0+i] < 0){//不是陷阱
                ;//沒事
            }
            else if(position[0+i] > 0){//是陷阱，若最外行比最高行低就優先放
                return (1+i);
            }
            else{
                //否則放1和4中分數高的
                if(posScore[1+i] > posScore[4+i]){
                    return (1+i);
                }
                else if(posScore[1+i] < posScore[4+i]){
                    return (4+i);
                }
                else{//等高
                    if(rand()%2==0){
                        return (4+i);
                    }
                }
            }
        }
    }
    std::reverse(pretrap.begin(), pretrap.end());//變{5,4,2,1,1}
    //右上左下
    //case3:{5,4,2,1,1,可,?}
    //case4:{?,5,4,2,1,1,可}
    for(int i=0; i<=1; i++){//i=0->case3,i=1-<case4
        //case4的數字都是case3+1
        
        std::copy(position.begin()+i+1, position.begin()+i+1+5, subPosition.begin());
        if(subPosition==pretrap){
            if((board[position[2+i]+1][2+i] != player)||(board[position[3+i]+1][3+i] != player)){//兩個中間的(2+i,3+i)空位往下一格不是自己
                ;//沒事
            }
            if(position[5+i] < 0){//不是陷阱
                ;//沒事
            }
            else if(position[5+i] > 0){//是陷阱，若最外行比最高行低就優先放最外第二行
                return (4+i);
            }
            else{
                //否則放1和4中分數高的
                if(posScore[1+i] > posScore[4+i]){
                    return (1+i);
                }
                else if(posScore[1+i] < posScore[4+i]){
                    return (4+i);
                }
                else{//等高
                    if(rand()%2==0){
                        return (4+i);
                    }
                }
            }
        }
    }
    return trap;//不能設陷阱，此處回傳值為-1
    
}





