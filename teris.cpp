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
  
        Map create_hitset(){
            Map hitset;
                if(pos2>=0){
                    for(int i= 0; i<= pos2; i++){
                        hitset.insert(Pair(pos1+i, bottom1));
                    }
                }
                else{
                    for(int i= 0; i<= ((-1)*pos2); i++){
                        hitset.insert(Pair(pos1-i, bottom1));
                    }
                }
            return hitset;   
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
        int pos1i= string_to_int(pos1)-1;
        int pos2i= string_to_int(pos2);
        if((pos1i+pos2i)>coli||(pos1i+pos2i)<0)
            break;
        int bottom1= table.get_bottom(pos1i);
        Block block(pos1i, pos2i, bottom1, shape);
        Map hitset= block.create_hitset();
        isend= table.check_ishit(hitset);
        cout<<isend<<endl;
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
