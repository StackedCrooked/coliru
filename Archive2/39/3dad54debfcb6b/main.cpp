#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

// From 11/15/14; JOB PEGS program hopefully

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct Board {int t[6][6]; int move; bool moved; int moves[15]; 
    };


void PrintIt(Board b){
//    for (int x=0; x<6; x++) {
//        for (int y=0; y<6; y++) {
std::cout   <<b.t[0][0] <<"\t\t\t\t"<<1<<","<<1<<":"<<b.t[1][1]<<" ";
for (int x=1; x<15; x++) {std::cout<<b.moves[x]<<",";}
std::cout<<"\n";

std::cout               <<"\t\t\t"  <<1<<","<<2<<":"<<b.t[1][2]<<"\t\t"<<2<<","<<2<<":"<<b.t[2][2]<<"\n";
std::cout               <<"\t\t"    <<1<<","<<3<<":"<<b.t[1][3]<<"\t\t"<<2<<","<<3<<":"<<b.t[2][3]<<"\t\t"<<3<<","<<3<<":"<<b.t[3][3]<<"\n";
std::cout               <<"\t"      <<1<<","<<4<<":"<<b.t[1][4]<<"\t\t"<<2<<","<<4<<":"<<b.t[2][4]<<"\t\t"<<3<<","<<4<<":"<<b.t[3][4]<<"\t\t"<<4<<","<<4<<":"<<b.t[4][4]<<"\n";
std::cout                           <<1<<","<<5<<":"<<b.t[1][5]<<"\t\t"<<2<<","<<5<<":"<<b.t[2][5]<<"\t\t"<<3<<","<<5<<":"<<b.t[3][5]<<"\t\t"<<4<<","<<5<<":"<<b.t[4][5]<<"\t\t"<<5<<","<<5<<":"<<b.t[5][5]<<"\n";
std::cout << "Altered " << b.moved;
//std::cout << x << "," << y << ":" << b.t[x][y] << "\t";
//        }
//        std:: cout << std::endl;
//    }
    std:: cout << std::endl;
}
 
void ListMoves(Board& b)
{
    int num = 0;
        for (int x=0; x<6; x++) {
            for (int y=0; y<6; y++) {
                //std::cout << "Checking:" << x << "," << y << "\n";
                //if (b.t[x][y]==1)
                //{
                // brute force go thru the board for a move and do it then rucurse; so I and my kids can read it.
                if ((x==1) && (y==1)) {
                    if ((b.t[1][1]==1) && (b.t[1][2]==1) && (b.t[1][3]==0)) {b.moves[num++]=1113; }
                    if ((b.t[1][1]==1) && (b.t[2][2]==1) && (b.t[3][3]==0)) {b.moves[num++]=1133; }
                    }
                if ((x==1) && (y==2)) {
                    if ((b.t[1][2]==1) && (b.t[1][3]==1) && (b.t[1][4]==0)) {b.moves[num++]=1214; }
                    if ((b.t[1][2]==1) && (b.t[2][3]==1) && (b.t[3][4]==0)) {b.moves[num++]=1234; }
                    }
                if ((x==1) && (y==3)) {
                    if ((b.t[1][3]==1) && (b.t[1][2]==1) && (b.t[1][1]==0)) {b.moves[num++]=1311; }
                    if ((b.t[1][3]==1) && (b.t[1][4]==1) && (b.t[1][5]==0)) {b.moves[num++]=1315; }
                    if ((b.t[1][3]==1) && (b.t[2][3]==1) && (b.t[3][3]==0)) {b.moves[num++]=1333; }
                    if ((b.t[1][3]==1) && (b.t[2][4]==1) && (b.t[3][5]==0)) {b.moves[num++]=1335; }
                    }
                if ((x==1) && (y==4)) {
                    if ((b.t[1][4]==1) && (b.t[1][3]==1) && (b.t[1][2]==0)) {b.moves[num++]=1412; }
                    if ((b.t[1][4]==1) && (b.t[2][4]==1) && (b.t[3][4]==0)) {b.moves[num++]=1434; }
                    }
                if ((x==1) && (y==5)) {
                    if ((b.t[1][5]==1) && (b.t[1][4]==1) && (b.t[1][3]==0)) {b.moves[num++]=1513; }
                    if ((b.t[1][5]==1) && (b.t[2][5]==1) && (b.t[3][5]==0)) {b.moves[num++]=1535; }
                    }
                if ((x==2) && (y==2)) {
                    if ((b.t[2][2]==1) && (b.t[3][3]==1) && (b.t[4][4]==0)) {b.moves[num++]=2244; }
                    if ((b.t[2][2]==1) && (b.t[2][3]==1) && (b.t[2][4]==0)) {b.moves[num++]=2224; }
                    }
                if ((x==2) && (y==3)) {
                    if ((b.t[2][3]==1) && (b.t[2][4]==1) && (b.t[2][5]==0)) {b.moves[num++]=2325; }
                    if ((b.t[2][3]==1) && (b.t[3][4]==1) && (b.t[4][5]==0)) {b.moves[num++]=2345; }
                    }
                if ((x==2) && (y==4)) {
                    if ((b.t[2][4]==1) && (b.t[2][3]==1) && (b.t[2][2]==0)) {b.moves[num++]=2422; }
                    if ((b.t[2][4]==1) && (b.t[3][4]==1) && (b.t[4][4]==0)) {b.moves[num++]=2444; }
                    }
                if ((x==2) && (y==5)) {
                    if ((b.t[2][5]==1) && (b.t[2][4]==1) && (b.t[2][3]==0)) {b.moves[num++]=2523; }
                    if ((b.t[2][5]==1) && (b.t[3][5]==1) && (b.t[4][5]==0)) {b.moves[num++]=2545; }
                    }
                if ((x==3) && (y==3)) {
                    if ((b.t[3][3]==1) && (b.t[2][3]==1) && (b.t[1][3]==0)) {b.moves[num++]=3313; }
                    if ((b.t[3][3]==1) && (b.t[2][2]==1) && (b.t[1][1]==0)) {b.moves[num++]=3311; }
                    if ((b.t[3][3]==1) && (b.t[4][4]==1) && (b.t[5][5]==0)) {b.moves[num++]=3355; }
                    if ((b.t[3][3]==1) && (b.t[3][4]==1) && (b.t[3][5]==0)) {b.moves[num++]=3335; }
                    }
                if ((x==3) && (y==4)) {
                    if ((b.t[3][4]==1) && (b.t[2][3]==1) && (b.t[1][2]==0)) {b.moves[num++]=3412; }
                    if ((b.t[3][4]==1) && (b.t[2][4]==1) && (b.t[1][4]==0)) {b.moves[num++]=3414; }
                    }
                if ((x==3) && (y==5)) {
                    if ((b.t[3][5]==1) && (b.t[2][5]==1) && (b.t[1][5]==0)) {b.moves[num++]=3515; }
                    if ((b.t[3][5]==1) && (b.t[4][5]==1) && (b.t[5][5]==0)) {b.moves[num++]=3555; }
                    if ((b.t[3][5]==1) && (b.t[2][4]==1) && (b.t[1][3]==0)) {b.moves[num++]=3513; }
                    if ((b.t[3][5]==1) && (b.t[3][4]==1) && (b.t[3][3]==0)) {b.moves[num++]=3533; }
                    }
                if ((x==4) && (y==4)) {
                    if ((b.t[4][4]==1) && (b.t[3][3]==1) && (b.t[2][2]==0)) {b.moves[num++]=4422; }
                    if ((b.t[4][4]==1) && (b.t[3][4]==1) && (b.t[2][4]==0)) {b.moves[num++]=4424; }
                    }
                if ((x==4) && (y==5)) {
                    if ((b.t[4][5]==1) && (b.t[3][4]==1) && (b.t[2][3]==0)) {b.moves[num++]=4523; }
                    if ((b.t[4][5]==1) && (b.t[3][5]==1) && (b.t[2][5]==0)) {b.moves[num++]=4525; }
                    }
                if ((x==5) && (y==5)) {
                    if ((b.t[5][5]==1) && (b.t[4][4]==1) && (b.t[3][3]==0)) {b.moves[num++]=5533; }
                    if ((b.t[5][5]==1) && (b.t[4][5]==1) && (b.t[3][5]==0)) {b.moves[num++]=5535; }
                    }
            }         
        }
        b.move=num;
    for (int x=0;x<15;x++) {std::cout << b.moves[x] << " ";} std::cout<<b.move<<"\n";
    return;
}



int main()
{       
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

Board b;
for (int x=0; x<6; x++) {
    for (int y=0; y<6; y++) {
        b.t[x][y] = 1;
    }
}

//for (int x=0; x<15; x++) {
//        b.moves[x] = 0;
//}
//vector<int> bm(1,0);
vector<Board> b0(1);
for (int x=0; x<6; x++) {
    for (int y=0; y<6; y++) {
        b0.at(0).t[x][y] = 1;
    }
}

b0.at(0).t[0][0] = 0;// moves
b0.at(0).t[0][1] = 0;// move from next
b0.at(0).t[0][2] = 0;// move to next
b0.at(0).t[0][3] = 0;// pegs on board
b0.at(0).t[0][4] = 1;// Moves remaining
b0.at(0).t[5][5] = 0;
//b0.at(0).t[1][5] = 0;
//b0.at(0).t[5][5] = 0;


Board b1;

b0.push_back(b1);

std::for_each(b0.begin(), b0.end()-1, ListMoves); 
    for (int x=0;x<15;x++) {std::cout << b0.at(0).moves[x] << " ";} std::cout<<b0.at(0).move<<"\n";

}
