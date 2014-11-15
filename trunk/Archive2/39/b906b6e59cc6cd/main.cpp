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
void PrintIt(int arr[6][6]){
for (x=0; x<6; x++) {
     for (y=0; y<6; y++) {
        std::cout << x << "," << y << ":" << arr[x][y] << "___";
    }
    std:: cout << std::endl;
}   
}



void JumpIt(int arr[6][6], int ax, int ay, int bx, int by, int cx, int cy){
arr[ax][ay] = 0;
arr[bx][by] = 0;
arr[cx][cy] = 1;
arr[0][0]--;

return;
}

void Move(int arr[6][6])
{
    printf("MOVE_");
 for (int x=0; x>0; x++) {
    for (int y=0; y>0; y++) {
        if (arr[x][y]==1)
         {
            // brute force go thru the board for a move and do it then rucurse; so I and my kids can read it.
            if ((x==1) && (y==1)) {
                if ((arr[1][1]==1) && (arr[1][2]==1) && (arr[1][3]==0)) { JumpIt(arr, 1,1,1,2,1,3); }
                if ((arr[1][1]==1) && (arr[2][2]==1) && (arr[3][3]==0)) { JumpIt(arr, 1,1,2,2,3,3); }
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
table[0][0] = 14;    //Set the initial pegs count

for (x=0; x<6; x++) {
     for (y=0; y<6; y++) {
        std::cout << x << "," << y << ":" << table[x][y] << "___";
    }
    std:: cout << std::endl;
}
Move(table);
}
