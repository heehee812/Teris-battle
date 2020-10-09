#include <bits/stdc++.h>
using namespace std;

/*------------shared variable--------------*/
typedef vector<int> Col;
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
};

class Table{
    private:
        int row, col;
        vector<Col> nonzerotable, bombtable;
    public:
        Table(int n, int m): row(n), col(m){
            nonzerotable.reserve(col);
            for(int i= 0; i<col; i++){
                nonzerotable[i].emplace_back(0);
            }
            for (int i= 0; i<col; i++)
            {
                for (auto j: nonzerotable[i])
                    std::cout << j << " ";
                std::cout << '\n';
            }
        }
        // int get_bottom(int pos1){}
  
};

class Block: public GameBoard{
    private:
        int pos1, pos2, bottom1;
        char *kind;
    public:
        Block(int x1, int x2, char *shape): pos1(x1), pos2(x2), kind(shape){
        }
        void check_is_hit(){
            int dir= kind[1]-'0';
            switch(kind[0]){
                case(73):{ //I
                    switch(dir){
                        case(1):{
                            break;
                        }
                        case(2):{
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                }
                case(74):{ //J
                    switch(dir){
                        case(1):{
                            break;
                        }
                        case(2):{
                            break;
                        }
                        case(3):{
                            break;
                        }
                        case(4):{
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                }
                case(76):{ //L
                    switch(dir){
                        case(1):{
                            break;
                        }
                        case(2):{
                            break;
                        }
                        case(3):{
                            break;
                        }
                        case(4):{
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                } 
                case(79):{ //O
                    break;
                }
                case(83):{ //S
                    switch(dir){
                        case(1):{
                            break;
                        }
                        case(2):{
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                }
                case(84):{ //T
                    switch(dir){
                        case(1):{
                            break;
                        }
                        case(2):{
                            break;
                        }
                        case(3):{
                            break;
                        }
                        case(4):{
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                }
                case(90):{ //Z
                    switch(dir){
                        case(1):{
                            break;
                        }
                        case(2):{
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                }
                default:{
                    game_over(1);
                }
            }
        }
        void assign_to_gameboard(){}
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
    GameBoard gameboard(rowi, coli);
    Table table(rowi, coli);
    // gameboard.print_gameboard();

    //load in a test case
    while(!ifile.eof()){
        if(isend)
            break;
        read_file(shape, pos1, pos2, &ifile);
        int pos1i= string_to_int(pos1);
        int pos2i= string_to_int(pos2);
        Block block(pos1i, pos2i, shape);
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
    while(*word){
        if((*word)<=47);
        else{
            number= (number*10)+ (*word-'0');
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
