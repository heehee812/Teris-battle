#include <bits/stdc++.h>
using namespace std;

/*------------shared variable--------------*/
typedef vector<int> Col;
typedef map<int, int> Map;
typedef pair<int, int> Pair;
int isend= 0;
/*------------shared function--------------*/
void read_file(char *, char *, char *, fstream *);
int string_to_int(const char *);
void game_over(int);

/*-----------------class-------------------*/
class GameBoard{
    protected:
        int row, col;
        int **gameboard;
    public:
        GameBoard(int n, int m): row(n), col(m){
            cout<<"---------------Start------------------"<<endl;
            gameboard= new_gameboard(row, col);
        }
        GameBoard(){}
        int** new_gameboard(int n, int m){
            int ele= 0;
            int **element= new int*[n];
            for(int i=0; i<n; i++){
                element[i]= new int[m];
            }
            for(int i=0; i<n; i++)
                for(int j= 0; j<m; j++){
                    element[i][j]= 0;
                }
            return element;
        }

        void print_gameboard(){
            for(int i=0; i<row; i++){
                for(int j= 0; j<col; j++){
                    cout<<gameboard[i][j];
                }
                cout<<endl;
            }
        }
        void assign_block(){

        }
};

class Table{
    private:
        int row, col;
        vector<Col> nonzerotable, bombtable;
    public:
        Table(int n, int m): row(n), col(m){
            nonzerotable.reserve(col);
            for(int i= 0; i<col; i++){
                nonzerotable[i].emplace_back(-1);
            }
            // for (int i= 0; i<col; i++)
            // {
            //     for (auto j: nonzerotable[i])
            //         std::cout << j << " ";
            //     std::cout << '\n';
            // }
        }
        void update_nonzerotable(){
        }
        int get_bottom(int pos1){
            int end= nonzerotable[pos1].size()-1;
            return nonzerotable[pos1][end]+1;
        }
        int check_ishit(Map hitset){
            for(auto &it: hitset){
                for(auto i: nonzerotable[it.second])
                {
                    if(i==it.first){
                        cout<<"("<<it.first<<", "<<it.second<<")"<<endl;
                        return 1;
                    }
                    else{
                        continue;
                    }
                }
            }
            return 0;
        }  
};

class Block: public GameBoard{
    private:
        int pos1, pos2, bottom1;
        char *kind;
    public:
        Block(int x1, int x2, int y1, char *shape): pos1(x1), pos2(x2), bottom1(y1), kind(shape){
        }
        Map create_hitset();
        // void assign_to_gameboard(){}
};



/*---------------main function-----------------*/
int main(){
    char row[2], col[5], shape[3], pos1[4], pos2[4];

    //load in a test case
    string filename= "1.data";
    fstream ifile(filename, ios::in);

    //get the size of the game board
    ifile.getline(row, sizeof(row), ' ');
    ifile.getline(col, sizeof(col), '\n');
    int rowi= string_to_int(row);
    int coli= string_to_int(col);
    GameBoard gb(rowi, coli);
    Table table(rowi, coli);
    // gameboard.print_gameboard();

    //load in a test case
    while(!ifile.eof()){
        if(isend)
            break;
        //load in block   
        read_file(shape, pos1, pos2, &ifile);
        int pos1i= string_to_int(pos1)-1;
        int pos2i= string_to_int(pos2);

        //check if input invalid
        if((pos1i+pos2i)>coli||(pos1i+pos2i)<0)
            break;

        //check if hit
        int bottom1= table.get_bottom(pos1i);
        Block block(pos1i, pos2i, bottom1, shape);
        Map hitset= block.create_hitset();
        if(!hitset.empty()){
            isend= table.check_ishit(hitset);
            if(isend)
                game_over(1);
        }

        //assign to gameboard and nonzerotable
        table.update_nonzerotable();
        gb.assign_block();
    }
    ifile.close();
    return 0;
}


/*------------shared function--------------*/
void read_file(char *shape, char *pos1, char *pos2, fstream *ifile){
    (*ifile).getline(shape, sizeof(shape), ' ');
    if(shape[0]== 69)
        game_over(0);
    else{
        (*ifile).getline(pos1, sizeof(pos1), ' ');
        (*ifile).getline(pos2, sizeof(pos2), '\n');
    }
}

int string_to_int(const char *word){
    int number= 0;
    int isminor= 0;
    while(*word){
        if((*word)<=47&&(*word)!=45);
        else{
            if(*word==45){
                isminor= 1;
            }
            else{
                number= (number*10)+ (*word-'0');
                if(isminor){
                    number= number*(-1);
                    isminor= 0;
                }
            }
        }
        word++;
    }
    return number;
}

void game_over(int i){
    if(i)
        cout<<"---------------GAME OVER------------------"<<endl;
    else
        cout<<"---------------End------------------"<<endl;
    isend= 1;
}

/*------------member function--------------*/
Map Block:: create_hitset(){
            int dir= kind[1]-'0';
            int lpos, rpos; //the lftest and the rightest point of the block
            Map hitset;
            if(pos2== 0);
            else if(pos2>0){
                switch(kind[0]){
                    case(73):{ //I
                        switch(dir){
                            case(1):{
                                lpos= pos1;
                                for(int i= 0; i<4; i++){
                                    for(int j= 1; j<= pos2; j++){
                                        hitset.insert(Pair(lpos+j, bottom1+i));
                                    }
                                }
                                break;
                            }
                            case(2):{
                                lpos= pos1+3;
                                for(int j= 1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1));
                                }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(74):{ //J
                        switch(dir){
                            lpos= pos1+1;
                            case(1):{
                                for(int i= 0; i<=3; i++)
                                    for(int j= 1; j<= pos2; j++){
                                        hitset.insert(Pair(lpos+j, bottom1+i));
                                    }
                                break;
                            }
                            case(2):{
                                lpos= pos1+2;
                                for(int j= 1; j<= pos2; j++)
                                    hitset.insert(Pair(lpos+j, bottom1));
                                break;
                            }
                            case(3):{
                                lpos= pos1+1;
                                for(int j= 1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1+2));
                                }
                                for(int i= 0; i< 2; i++)
                                    for(int j= 1; j<= pos2; j++){
                                        hitset.insert(Pair(pos1+j, bottom1+i));
                                    }
                                break;
                            }
                            case(4):{
                                lpos= pos1+2;
                                for(int i= 0; i< 2; i++)
                                    for(int j= 1; j<= pos2; j++){
                                        hitset.insert(Pair(lpos+j, bottom1+i));
                                    }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(76):{ //L
                        switch(dir){
                            case(1):{
                                 lpos= pos1+1;
                                for(int j= 1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1));
                                }
                                for(int i= 1; i<= 2; i++)
                                    for(int j= 1; j<= pos2; j++){
                                        hitset.insert(Pair(pos1+j, bottom1+i));
                                    }
                                break;
                            }
                            case(2):{
                                lpos= pos1+2;
                                for(int j= 1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1+1));
                                    hitset.insert(Pair(pos1+j, bottom1));
                                }
                                break;
                            }
                            case(3):{
                                lpos= pos1+1;
                                for(int i= 0; i<3; i++)
                                    for(int j= 1; j<=pos2; pos2++){
                                        hitset.insert(Pair(lpos+j, bottom1+i));
                                    }
                                break;
                            }
                            case(4):{
                                lpos= pos1+2;
                                for(int i= 0; i<2; i++)
                                    for(int j= 1; j<=pos2; j++){
                                        hitset.insert(Pair(lpos+j, bottom1+i));
                                    } 
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    } 
                    case(79):{ //O
                        lpos= pos1+1;
                        for(int i= 0; i<2; i++)
                            for(int j= 1; j<= pos2; j++){
                                hitset.insert(Pair(lpos+j, bottom1+i));
                            }
                        break;
                    }
                    case(83):{ //S
                        switch(dir){
                            case(1):{
                                lpos= pos1+1;
                                for(int j= 1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1+1));
                                    hitset.insert(Pair(pos1+j, bottom1));
                                }
                                break;
                            }
                            case(2):{
                                lpos= pos1+ 1;
                                for(int i= 0; i<2; i++)
                                    for(int j= 1; j<= pos2; j++){
                                        hitset.insert(Pair(lpos+j, bottom1+i));
                                    }
                                for(int j=1; j<=pos2; j++){
                                    hitset.insert(Pair(pos1+j, bottom1+2));
                                }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(84):{ //T
                        switch(dir){
                            case(1):{
                                lpos= pos1+1;
                                for(int j=1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1+1));
                                    hitset.insert(Pair(pos1+j, bottom1));
                                }
                                break;
                            }
                            case(2):{
                                lpos= pos1+1;
                                for(int i = 0; i<3; i++)
                                    for(int j= 1; j<=pos2; j++){
                                        hitset.insert(Pair(lpos+j, bottom1+i));
                                    }
                                break;
                            }
                            case(3):{
                                lpos= pos1+2;
                                for(int j= 1; j<=pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1));
                                    hitset.insert(Pair(pos1+j, bottom1+1));
                                }
                                break;
                            }
                            case(4):{
                                lpos= pos1+1;
                                for(int j= 1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1+1));
                                    hitset.insert(Pair(pos1+j, bottom1));
                                    hitset.insert(Pair(pos1+j, bottom1+2));
                                }
                                break;
                            }
                           default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(90):{ //Z
                        switch(dir){
                            case(1):{
                                lpos= pos1+2;
                                for(int j=1; j<=pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1));
                                    hitset.insert(Pair(pos1+j, bottom1+1));
                                }
                                break;
                            }
                            case(2):{
                                lpos= pos1+ 1;
                                rpos= bottom1+1;
                                for(int i= 0; i<2; i++)
                                    for(int j= 1; j<= pos2; j++){
                                        hitset.insert(Pair(lpos+j, rpos+i));
                                    }
                                for(int j=1; j<=pos2; j++){
                                    hitset.insert(Pair(pos1+j, bottom1));
                                }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(69):{
                        game_over(0);
                    }
                    default:{
                        game_over(1);
                    }
                }
            }
            else{
                switch(kind[0]){
                    case(73):{ //I
                        switch(dir){
                            case(1):{
                                for(int i=0; i<4; i++)
                                    for(int j =1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                break;
                            }
                            case(2):{
                                for(int j =1; j<=(-pos2); j++){
                                    hitset.insert(Pair(pos1-j, bottom1));
                                }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(74):{ //J
                        switch(dir){
                            case(1):{
                                for(int j= 1; j<=(-pos2); j++){
                                    hitset.insert(Pair(pos1-j, bottom1));
                                }
                                for(int i= 0; i<3; i++)
                                    for(int j= 1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                break;
                            }
                            case(2):{
                                for(int i= 0; i<2; i++){
                                    for(int j= 1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                }
                                break;
                            }
                            case(3):{
                                for(int i= 0; i<3; i++)
                                    for(int j=1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                break;
                            }
                            case(4):{
                                lpos= pos1+2;
                                for(int j= 1; j<=(-pos2); j++){
                                    hitset.insert(Pair(pos1-j, bottom1+1));
                                    hitset.insert(Pair(lpos-j, bottom1));
                                }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(76):{ //L
                        switch(dir){
                            case(1):{
                                for(int i= 0; i<3; i++)
                                    for(int j=1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                break;
                            }
                            case(2):{
                                for(int i= 0; i<2; i++){
                                    for(int j= 1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                }
                                break;
                            }
                            case(3):{
                                lpos= pos1+1;
                                for(int j=1; j<=(-pos2); j++){
                                    hitset.insert(Pair(pos1-j, bottom1+2));
                                }
                                for(int i= 0; i<2; i++)
                                    for(int j= 1; j<=(-pos2); j++){
                                        hitset.insert(Pair(lpos-j, bottom1+i));
                                    }
                                break;
                            }
                            case(4):{
                                lpos= pos1+2;
                                for(int j=1; j<=(-pos2); j++){
                                    hitset.insert(Pair(pos1-j,bottom1+1));
                                    hitset.insert(Pair(lpos-j, bottom1));
                                }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    } 
                    case(79):{ //O
                        for(int i=0; i<2; i++)
                            for(int j= 1; j<=(-pos2); j++){
                                hitset.insert(Pair(lpos-j, bottom1+i));
                            }
                        break;
                    }
                    case(83):{ //S
                        switch(dir){
                            case(1):{
                                lpos= pos1+1;
                                for(int j=1; j<=(-pos2); j++){
                                    hitset.insert(Pair(pos1-j, bottom1));
                                    hitset.insert(Pair(lpos-j, bottom1+1));
                                }
                                break;
                            }
                            case(2):{
                                lpos= pos1+1;
                                rpos= bottom1+1;
                                for(int j=1; j<=(-pos2); j++){
                                    hitset.insert(Pair(lpos-j, bottom1));
                                }
                                for(int i=0; i<2; i++)
                                    for(int j=1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, rpos+i));
                                    }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(84):{ //T
                        switch(dir){
                            case(1):{
                                lpos= pos1+1;
                                for(int j= 1; j<=(-pos2); j++){
                                    hitset.insert(Pair(lpos-j, bottom1));
                                    hitset.insert(Pair(pos1-j, bottom1+1));
                                }
                                break;
                            }
                            case(2):{
                                lpos= pos1+1;
                                for(int j= 1; j<=(-pos2); j++){
                                    hitset.insert(Pair(pos1-j, bottom1+1));
                                    hitset.insert(Pair(lpos-j, bottom1));
                                    hitset.insert(Pair(lpos-j, bottom1+2));
                                }
                                break;
                            }
                            case(3):{
                                lpos= pos1+1;
                                for(int j= 1; j<=(-pos2); j++){
                                    hitset.insert(Pair(lpos-j, bottom1+1));
                                    hitset.insert(Pair(pos1-j, bottom1));
                                }
                                break;
                            }
                            case(4):{
                                for(int i= 0; i<3; i++)
                                    for(int j=1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(90):{ //Z
                        switch(dir){
                            case(1):{
                                lpos= pos1+1;
                                for(int j= 1; j<=(-pos2); j++){
                                    hitset.insert(Pair(lpos-j, bottom1));
                                    hitset.insert(Pair(pos1-j, bottom1+1));
                                }
                                break;
                            }
                            case(2):{
                                lpos= pos1+1;
                                for(int j= 1; j<=(-pos2); j++){
                                    hitset.insert(Pair(lpos-j, bottom1+2));
                                }
                                for(int i= 0; i<2; i++)
                                    for(int j= 1; j<=(-pos2); j++){
                                        hitset.insert(Pair(pos1-j, bottom1+i));
                                    }
                                break;
                            }
                            default:{
                                cout<<"[Input Invalid] ";
                                game_over(1);
                            }
                        }
                        break;
                    }
                    case(69):{
                        game_over(0);
                        break;
                    }
                    default:{
                        game_over(1);
                    }
                }
            }
            return hitset;   
        }

