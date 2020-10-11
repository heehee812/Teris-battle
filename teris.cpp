#include <bits/stdc++.h>
using namespace std;

/*------------shared variable--------------*/
typedef vector<int> Col;
typedef multimap<int, int> Map;
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
    public:
        vector<Col> gameboard;
        GameBoard(int n, int m): row(n), col(m){
            cout<<"---------------Start------------------"<<endl;
            new_gameboard(row, col);
        }
        GameBoard(){}
        void new_gameboard(int n, int m){
            gameboard.resize(row, vector<int>(col, 0));
        }

        void print_gameboard(){
            cout<<"gameboard: "<<endl;
            for(int i=0; i<row; i++){
                for(int j= 0; j<col; j++){
                    cout<<gameboard[i][j];
                }
                cout<<endl;
            }
            cout<<endl;
        }
        void bomb_gameboard(int i){
                vector<Col> tmp= gameboard;
                tmp.erase(tmp.begin()+row-1-i);
                gameboard= tmp;
                vector<int> v;
                v.resize(col, 0);
                gameboard.insert(gameboard.begin(),v); 
        }
};

class Block{
    private:
        int pos1, pos2, bottom1;
        char *kind;
    public:
        Block(int x1, int x2, int y1, char *shape): pos1(x1), pos2(x2), bottom1(y1), kind(shape){
        }
        Map create_hitset();
        int get_pos(){
            return pos2+pos1;
        }
        char* get_kind(){
            return kind;
        }
};

class Table{
    private:
        int row, col;
        vector<Col> nonzerotable, &gameboard;
        vector<int> bombtable;
    public:
        Table(int n, int m, vector<Col> &gb): row(n), col(m), gameboard(gb){
            nonzerotable.reserve(col);
            for(int i= 0; i<col; i++){
                nonzerotable[i].emplace_back(-1);
            }
            for(int i= 0; i<row; i++){
                bombtable.emplace_back(0);
            }
        }
        int get_bottom(int pos1){
            int end= nonzerotable[pos1].size()-1;
            return nonzerotable[pos1][end]+1;
        }
        void update_table(Block block);
        void sort_table(int sortrow){
            sort(nonzerotable[sortrow].begin(), nonzerotable[sortrow].end());
        }
        //---------print---------
        void print_nonzerotable(){
            cout<<"nonzerotable: "<<endl;
            for(int i= 0; i<col; i++)
            {
                for (auto j: nonzerotable[i])
                    cout << j << " ";
                cout << '\n';
            }
            cout<<endl;
        }
        void print_bombtable(){
            cout<<"bombtable: ";
            for(int i= 0; i<row; i++)
                cout<<bombtable[i] <<" ";
            cout<<endl;
        } 
        //---------check---------
        int check_ishit(Map hitset){
            for(auto &it: hitset){
                for(auto i: nonzerotable[it.first]){
                    if(i== it.second)
                        return 1;
                    else
                        return 0;
                }
            }
            return 0;
        }
        int check_isbomb(int i){
            if(bombtable[i]==col){
                return 1;
            }
            return 0;
        }
        //---------deal with the check---------
        void bomb_nonzerotable(int i){
                for(int c= 0; c<col; c++){
                    nonzerotable[c].erase(nonzerotable[c].begin()+i+1);
                    for(int r= i+1; r<nonzerotable[c].size(); r++){
                        --nonzerotable[c][r];
                    }
                }
        }
        void bomb_bombtable(int i){
            bombtable.erase(bombtable.begin()+i);
            bombtable.emplace_back(0);
        }
};

/*---------------main function-----------------*/
int main(){
    char row[2], col[5], shape[3], pos1[4], pos2[4];
    int isbomb= 0;

    //load in a test case
    string filename= "1.data";
    fstream ifile(filename, ios::in);

    //get the size of the game board
    ifile.getline(row, sizeof(row), ' ');
    ifile.getline(col, sizeof(col), '\n');
    int rowi= string_to_int(row);
    int coli= string_to_int(col);
    GameBoard gb(rowi, coli);
    Table table(rowi, coli, gb.gameboard);

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

        //update gameboard, bombtable and nonzerotable
        table.update_table(block);

        //chek if isbomb
        int i= rowi;
        int count= 0;//row that should be check
        while(i--){
            isbomb= table.check_isbomb(count);
            if(isbomb){
                gb.bomb_gameboard(count);
                table.bomb_nonzerotable(count);
                table.bomb_bombtable(count);
            }
            else
            {
                count++;
            }
            
        }
    }
    table.print_nonzerotable();
    table.print_bombtable();
    gb.print_gameboard();
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
                                for(int j= 1; j<= pos2; j++){
                                    hitset.insert(Pair(lpos+j, bottom1));
                                    hitset.insert(Pair(pos1+j, bottom1+1));
                                }
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
                        for(int i=0; i<2; i++){
                            for(int j= 1; j<=(-pos2); j++){
                                hitset.insert(Pair(pos1-j, bottom1+i));
                            }
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

void Table::update_table(Block block){
            int pos= block.get_pos();
            int bottom2= get_bottom(pos);
            char *kind= block.get_kind();
            int dir= kind[1]-'0';
            switch(kind[0]){
                case(73):{ //I
                    switch(dir){
                        case(1):{
                            for(int i=0; i<4; i++){
                                nonzerotable[pos].emplace_back(bottom2+i);
                                ++bombtable[bottom2+i];
                                gameboard[(row-1)-(bottom2+i)][pos]= 1;
                            }
                            break;
                        }
                        case(2):{
                            for(int j= 0; j<4; j++){
                                nonzerotable[pos+j].emplace_back(bottom2);
                                ++bombtable[bottom2];
                                gameboard[(row-1)-(bottom2)][pos+j]= 1;
                            }
                            break;
                        }
                        default:{
                            game_over(1);
                        }
                    }
                    break;
                }
                case(74):{ //J
                    switch(dir){
                        case(1):{
                            for(int i= 0; i<3; i++){
                                nonzerotable[pos+1].emplace_back(bottom2+i);
                                ++bombtable[bottom2+i];
                                gameboard[(row-1)-(bottom2+i)][pos+1]= 1;
                            }
                            nonzerotable[pos].emplace_back(bottom2);
                            ++bombtable[bottom2];
                            gameboard[(row-1)-(bottom2)][pos]= 1;
                            break;
                        }
                        case(2):{
                            for(int j= 0; j<3; j++){
                                nonzerotable[pos+j].emplace_back(bottom2);
                                ++bombtable[bottom2];
                                gameboard[(row-1)-(bottom2)][pos+j]= 1;
                            }
                            nonzerotable[pos].emplace_back(bottom2+1);
                            ++bombtable[bottom2+1];
                            gameboard[(row-1)-(bottom2+1)][pos]= 1;
                            break;
                        }
                        case(3):{
                            for(int i= 0; i<3; i++){
                                nonzerotable[pos].emplace_back(bottom2+i);
                                ++bombtable[bottom2+i];
                                gameboard[(row-1)-(bottom2+i)][pos]= 1;
                            }
                            nonzerotable[pos+1].emplace_back(bottom2+2);
                            ++bombtable[bottom2+2];
                            gameboard[(row-1)-(bottom2+2)][pos+1]= 1;
                            break;
                        }
                        case(4):{
                            for(int j= 0; j<3; j++){
                                nonzerotable[pos+j].emplace_back(bottom2+1);
                                ++bombtable[bottom2+1];
                                gameboard[(row-1)-(bottom2+1)][pos+j]= 1;
                            }
                            nonzerotable[pos+2].emplace_back(bottom2);
                            ++bombtable[bottom2];
                            gameboard[(row-1)-(bottom2)][pos+2]= 1;
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
                            for(int i= 0; i<3; i++){
                                nonzerotable[pos].emplace_back(bottom2+i);
                                ++bombtable[bottom2+i];
                                gameboard[(row-1)-(bottom2+i)][pos]= 1;
                            }
                            nonzerotable[pos+1].emplace_back(bottom2);
                            ++bombtable[bottom2];
                            gameboard[(row-1)-(bottom2)][pos+1]= 1;
                            break;
                        }
                        case(2):{
                            for(int j= 0; j<3; j++){
                                nonzerotable[pos+j].emplace_back(bottom2+1);
                                ++bombtable[bottom2+1];
                                gameboard[(row-1)-(bottom2+1)][pos+j]= 1;
                            }
                            nonzerotable[pos].emplace_back(bottom2);
                            ++bombtable[bottom2];
                            gameboard[(row-1)-(bottom2)][pos]= 1;
                            break;
                        }
                        case(3):{
                            for(int i= 0; i<3; i++){
                                nonzerotable[pos+1].emplace_back(bottom2+i);
                                ++bombtable[bottom2+i];
                                gameboard[(row-1)-(bottom2+i)][pos+1]= 1;
                            }
                            nonzerotable[pos].emplace_back(bottom2+2);
                            ++bombtable[bottom2+2];
                            gameboard[(row-1)-(bottom2+2)][pos]= 1;
                            break;
                        }
                        case(4):{
                            for(int j= 0; j<3; j++){
                                nonzerotable[pos+j].emplace_back(bottom2+1);
                                ++bombtable[bottom2+1];
                                gameboard[(row-1)-(bottom2+1)][pos+j]= 1;
                            }
                            nonzerotable[pos+2].emplace_back(bottom2);
                            ++bombtable[bottom2];
                            gameboard[(row-1)-(bottom2)][pos+2]= 1;
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                } 
                case(79):{ //O
                    for(int i= 0; i<2; i++)
                        for(int j=0; j<2; j++){
                            nonzerotable[pos+j].emplace_back(bottom2+i);
                            ++bombtable[bottom2+i];
                            gameboard[(row-1)-(bottom2+i)][pos+j]= 1;
                        }
                    break;
                }
                case(83):{ //S
                    switch(dir){
                        case(1):{
                            for(int j= 0; j<2; j++){
                                nonzerotable[pos+j].emplace_back(bottom2);
                                nonzerotable[pos+1+j].emplace_back(bottom2+1);
                                ++bombtable[bottom2];
                                ++bombtable[bottom2+1];
                                gameboard[(row-1)-(bottom2)][pos+j]= 1;
                                gameboard[(row-1)-(bottom2+1)][pos+1+j]= 1;
                            }
                            break;
                        }
                        case(2):{
                                for(int i= 0; i<2; i++){
                                    nonzerotable[pos].emplace_back(bottom2+1+i);
                                    nonzerotable[pos+1].emplace_back(bottom2+i);
                                    ++bombtable[bottom2+1+i];
                                    ++bombtable[bottom2+i];
                                    gameboard[(row-1)-(bottom2+1+i)][pos]= 1;
                                    gameboard[(row-1)-(bottom2+i)][pos+1]= 1;
                                }
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
                            for(int j= 0; j<3; j++){
                                nonzerotable[pos+j].emplace_back(bottom2+1);
                                ++bombtable[bottom2+1];
                                gameboard[(row-1)-(bottom2+1)][pos+j]= 1;
                                }
                            nonzerotable[pos+1].emplace_back(bottom2);
                            ++bombtable[bottom2];
                            gameboard[(row-1)-(bottom2)][pos+1]= 1;
                            break;
                        }
                        case(2):{
                            for(int i= 0; i<3; i++){
                                nonzerotable[pos+1].emplace_back(bottom2+i);
                                ++bombtable[bottom2+i];
                                gameboard[(row-1)-(bottom2+i)][pos+1]= 1;
                            }
                            nonzerotable[pos].emplace_back(bottom2+1);
                            ++bombtable[bottom2+1];
                            gameboard[(row-1)-(bottom2+1)][pos]= 1;
                            break;
                        }
                        case(3):{
                            for(int j= 0; j<3; j++){
                                nonzerotable[pos+j].emplace_back(bottom2);
                                ++bombtable[bottom2];
                                gameboard[(row-1)-(bottom2)][pos+j]= 1;
                            }
                            nonzerotable[pos+1].emplace_back(bottom2+1);
                            ++bombtable[bottom2+1];
                            gameboard[(row-1)-(bottom2+1)][pos+1]= 1;
                            break;
                        }
                        case(4):{
                            for(int i= 0; i<3; i++){
                                nonzerotable[pos].emplace_back(bottom2+i);
                                ++bombtable[bottom2+i];
                                gameboard[(row-1)-(bottom2+i)][pos]= 1;
                            }
                            nonzerotable[pos+1].emplace_back(bottom2+1);
                            ++bombtable[bottom2+1];
                            gameboard[(row-1)-(bottom2+1)][pos+1]= 1;
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
                            for(int j= 0; j<2; j++){
                                nonzerotable[pos+j].emplace_back(bottom2+1);
                                nonzerotable[pos+1+j].emplace_back(bottom2);
                                ++bombtable[bottom2+1];
                                ++bombtable[bottom2];
                                gameboard[(row-1)-(bottom2+1)][pos+j]= 1;
                                gameboard[(row-1)-(bottom2)][pos+1+j]= 1;
                            }
                            break;
                        }
                        case(2):{
                            for(int i= 0; i<2; i++){
                                nonzerotable[pos].emplace_back(bottom2+i);
                                nonzerotable[pos+1].emplace_back(bottom2+1+i);
                                ++bombtable[bottom2+i];
                                ++bombtable[bottom2+1+i];
                                gameboard[(row-1)-(bottom2+i)][pos]= 1;
                                gameboard[(row-1)-(bottom2+1+i)][pos+1]= 1;
                            }
                            break;
                        }
                        default:
                            game_over(1);
                    }
                    break;
                }
                case(69):{
                    game_over(0);
                    break;
                }
                default:
                    game_over(1);
            }
            for(int i= 0; i<col; i++){
                sort_table(i);
            }
            for(int i= 0; i<col; i++){
                sort_table(i);
            }
        }

