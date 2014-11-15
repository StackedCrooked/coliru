#include <iostream>
#include <string>
#include <vector>
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

struct Board {int t[6][6]; int games; bool moved; 
    };


void PrintIt(Board b){
//    for (int x=0; x<6; x++) {
//        for (int y=0; y<6; y++) {
std::cout   <<b.t[0][0] <<"\t\t\t\t"<<1<<","<<1<<":"<<b.t[1][1]<<"\n";
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

void Move(Board b)
{
    b.games++;
    printf("Checking_\n");
    PrintIt(b);
    while (b.moved){
        b.moved=false;
        for (int x=0; x<6; x++) {
            for (int y=0; y<6; y++) {
                std::cout << "Checking:" << x << "," << y << "\n";
                //if (b.t[x][y]==1)
                //{
                // brute force go thru the board for a move and do it then rucurse; so I and my kids can read it.
                if ((x==1) && (y==1)) {
                    if ((b.t[1][1]==1) && (b.t[1][2]==1) && (b.t[1][3]==0)) {b.t[1][1]=0;b.t[1][1]=0;b.t[1][3]=1;b.t[0][0]--; b.moved=true; std::cout<<"Move "<<x<<","<<y<<" to 1,3"<<"\n"; Move(b); }
                    if ((b.t[1][1]==1) && (b.t[2][2]==1) && (b.t[3][3]==0)) {b.t[1][1]=0;b.t[2][2]=0;b.t[3][3]=1;b.t[0][0]--; b.moved=true; std::cout<<"Move "<<x<<","<<y<<" to 3,3"<<"\n"; Move(b); }
                        }
                if ((x==1) && (y==2)) {}
                if ((x==1) && (y==3)) {
                    if ((b.t[1][3]==1) && (b.t[1][2]==1) && (b.t[1][1]==0)) {b.t[1][3]=0;b.t[1][2]=0;b.t[1][1]=1;b.t[0][0]--; b.moved=true; std::cout<<"Move "<<x<<","<<y<<" to 1,1"<<"\n"; Move(b); }
                    if ((b.t[1][3]==1) && (b.t[1][4]==1) && (b.t[1][5]==0)) {b.t[1][3]=0;b.t[2][4]=0;b.t[1][5]=1;b.t[0][0]--; b.moved=true; std::cout<<"Move "<<x<<","<<y<<" to 1,5"<<"\n"; Move(b); }
                    if ((b.t[1][3]==1) && (b.t[2][3]==1) && (b.t[3][3]==0)) {b.t[1][3]=0;b.t[2][3]=0;b.t[3][3]=1;b.t[0][0]--; b.moved=true; std::cout<<"Move "<<x<<","<<y<<" to 3,3"<<"\n"; Move(b); }
                    }
                if ((x==1) && (y==4)) {}
                if ((x==1) && (y==5)) {
                    if ((b.t[1][5]==1) && (b.t[1][4]==1) && (b.t[1][3]==0)) {b.t[1][5]=0;b.t[1][4]=0;b.t[1][3]=1;b.t[0][0]--; b.moved=true; std::cout<<"Move "<<x<<","<<y<<" to 1,3"<<"\n"; Move(b); }
                    if ((b.t[1][5]==1) && (b.t[2][5]==1) && (b.t[3][5]==0)) {b.t[1][5]=0;b.t[2][5]=0;b.t[3][5]=1;b.t[0][0]--; b.moved=true; std::cout<<"Move "<<x<<","<<y<<" to 3,5"<<"\n"; Move(b); }
                    }
                if ((x==2) && (y==2)) {}
                if ((x==2) && (y==3)) {}
                if ((x==2) && (y==4)) {}
                if ((x==2) && (y==5)) {}
                if ((x==3) && (y==3)) {}
                if ((x==3) && (y==4)) {}
                if ((x==3) && (y==5)) {}
                if ((x==4) && (y==4)) {}
                if ((x==4) && (y==5)) {}
                if ((x==5) && (y==5)) {}
                //};
            }         
        }
    }
printf("DONE\n");
//PrintIt(b);    
return;
}



int main()
{    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;


//initialize
//struct Board {int t[6][6]={
//    {1,1,1,1,1,1},
//    {1,1,1,1,1,1},
//    {1,1,1,1,1,1},
//    {1,1,1,1,1,1},
//    {1,1,1,1,1,1},
//    {1,1,1,1,1,1}
//    };
//} b;

Board b;
for (int x=0; x<6; x++) {
    for (int y=0; y<6; y++) {
        b.t[x][y] = 1;
    }
}

b.t[3][3] = 0;    //Set the initial condition
b.t[0][0] = 14;    //Set the initial pegs count
b.moved=true;

PrintIt(b);
Move(b);
}
