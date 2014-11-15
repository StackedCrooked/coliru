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

void JumpIt(int ax, int ay, int bx, int by, int cx, int cy){
    return;
}

void Move(int arr[6][6])
{
    printf("hello");
 for (int x=0; x>0; x++) {
    for (int y=0; y>0; y++) {
        if (arr[x][y]==1)
         {
            // brute force go thru the board for a move and do it then rucurse; so I and my kids can read it.
            if ((x==1) && (y==1)) {
                if ((arr[1][1]==1) && (arr[1][2]==1) && (arr[1][3]==0)) { JumpIt(1,1,1,2,1,2); }
                }
            if ((x==2) && (y==1)) {}
            if ((x==2) && (y==1)) {}
            if ((x==3) && (y==1)) {}
            if ((x==3) && (y==2)) {}
            if ((x==3) && (y==3)) {}
            if ((x==4) && (y==1)) {}
            if ((x==4) && (y==2)) {}
            if ((x==4) && (y==3)) {}
            if ((x==4) && (y==4)) {}
            if ((x==5) && (y==1)) {}
            if ((x==5) && (y==2)) {}
            if ((x==5) && (y==3)) {}
            if ((x==5) && (y==4)) {}
            if ((x==5) && (y==5)) {}
         }
    ;
  }}
    
return;
}



int main()
{    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

int x;
int y;
int table[6][6]={
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1}
    };
table[1][1] = 0;    //Set the initial condition

for (x=0; x<6; x++) {
     for (y=0; y<6; y++) {
    //table[x][y]=1;
    std::cout << x << "," << y << ":" << table[x][x] << std::endl;

}}
  
Move(table);

}
