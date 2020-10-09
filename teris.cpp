#include <bits/stdc++.h>
using namespace std;

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
    char row[3], col[3], shape[4];
    int i= 0;
    fstream ifile("1.data", ios::in);
    ifile.getline(row, sizeof(row), ' ');
    ifile.getline(col, sizeof(col), '\n');
    if(!ifile.eof()){
        ifile.getline(shape, sizeof(shape), ' ');
    }
    cout<<row<<endl;
    cout<<col<<endl;
    cout<<shape<<endl;
    ifile.close();
    return 0;
}