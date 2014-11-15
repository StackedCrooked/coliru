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
    for (int x=0; x<6; x++) {
        for (int y=0; y<6; y++) {
            std::cout << x << "," << y << ":" << arr[x][y] << "\t";
        }
        std:: cout << std::endl;
    }
    std:: cout << std::endl;
}

void Move(int arr[6][6])
{
 printf("MOVE_\n");
 for (int x=0; x<6; x++) {
    for (int y=0; y<6; y++) {
        if (arr[x][y]==1)
         {
            // brute force go thru the board for a move and do it then rucurse; so I and my kids can read it.
            if ((x==1) && (y==1)) {
                if ((arr[1][1]==1) && (arr[1][2]==1) && (arr[1][3]==0)) {arr[1][1]=0;arr[1][1]=0;arr[1][3]=1;arr[0][0]--; Move(arr); }
                if ((arr[1][1]==1) && (arr[2][2]==1) && (arr[3][3]==0)) {arr[1][1]=0;arr[2][2]=0;arr[3][3]=1;arr[0][0]--; }
                }
            if ((x==1) && (y==2)) {}
            if ((x==1) && (y==3)) {
                if ((arr[1][3]==1) && (arr[1][2]==1) && (arr[1][3]==0)) {arr[1][1]=0;arr[1][1]=0;arr[1][3]=1;arr[0][0]--; Move(arr); }
                if ((arr[1][3]==1) && (arr[2][2]==1) && (arr[3][3]==0)) {arr[1][1]=0;arr[2][2]=0;arr[3][3]=1;arr[0][0]--; }
                }
            if ((x==1) && (y==4)) {}
            if ((x==1) && (y==5)) {}
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
         }
    ;
  }}
PrintIt(arr);    
return;
}



int main()
{    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

int table[6][6]={
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1}
    };
table[3][3] = 0;    //Set the initial condition
table[0][0] = 14;    //Set the initial pegs count

PrintIt(table);
Move(table);
}
