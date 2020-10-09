#include <bits/stdc++.h>
using namespace std;

void read_file(char *, char *, char *, fstream *);
int string_to_int(const char *);

class GameBoard{
    private:
        int row, col;
        int **gameboard;
    public:
        GameBoard(int n, int m): row(n), col(m){
            gameboard= new_game_board();
        }
        int** new_game_board(){
            int ele= 0;
            int **element= new int*[row];
            for(int i=0; i<row; i++){
                element[i]= new int[col];
            }
            for(int i=0; i<row; i++)
                for(int j= 0; j<col; j++){
                    element[i][j]= ele++;
                }
            return element;
        }
        void print_game_board(){
            for(int i=0; i<row; i++)
                for(int j= 0; j<col; j++){
                    cout<<gameboard[i][j];
                }
        }
};

int main(){
    char row[2], col[5], shape[3], pos1[4], pos2[4];
    string filename= "1.data";
    fstream ifile(filename, ios::in);

    //get the size of the game board
    ifile.getline(row, sizeof(row), ' ');
    ifile.getline(col, sizeof(col), '\n');
    int ro= string_to_int(row);
    int co= string_to_int(col);
    GameBoard gameboard(ro, co);
    // gameboard.print_game_board();


    while(!ifile.eof()){
        read_file(shape, pos1, pos2, &ifile);
    }
    ifile.close();
    return 0;
}

void read_file(char *shape, char *pos1, char *pos2, fstream *ifile){
    (*ifile).getline(shape, sizeof(shape), ' ');
    (*ifile).getline(pos1, sizeof(pos1), ' ');
    (*ifile).getline(pos2, sizeof(pos2), '\n');
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