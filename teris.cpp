#include <bits/stdc++.h>
using namespace std;

/*------------shared function--------------*/
void read_file(char *, char *, char *, fstream *);
int string_to_int(const char *);
void game_over();

/*-----------------class-------------------*/
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
        void seclect_block(int shape){
            switch(shape){
                case(73):{ //I
                    cout<<"select I"<<endl;
                    break;
                }
                case(74):{ //J
                    cout<<"select J"<<endl;
                    break;
                }
                case(76):{ //L
                    cout<<"select L"<<endl;
                    break;
                } 
                case(79):{ //O
                    cout<<"select O"<<endl;
                    break;
                }
                case(83):{ //S
                    cout<<"select S"<<endl;
                    break;
                }
                case(84):{ //T
                    cout<<"select T"<<endl;
                    break;
                }
                case(90):{ //Z
                    cout<<"select Z"<<endl;
                    break;
                }
                default:
                    game_over();
            }
        }
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
    // gameboard.print_game_board();

    //load in a test case
    while(!ifile.eof()){
        read_file(shape, pos1, pos2, &ifile);
        int pos1i= string_to_int(pos1);
        int pos2i= string_to_int(pos2);
        gameboard.seclect_block(shape[0]);
    }
    ifile.close();
    return 0;
}


/*------------shared function--------------*/
void read_file(char *shape, char *pos1, char *pos2, fstream *ifile){
    (*ifile).getline(shape, sizeof(shape), ' ');
    if(shape[0]== 69);
        // game_over();
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

void game_over(){
    cout<<"---------------GAME OVER------------------"<<endl;
}
