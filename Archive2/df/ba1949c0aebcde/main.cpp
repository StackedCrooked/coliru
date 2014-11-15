#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void Move(int arr[5][5])
{
    printf("hello");
 for (int x=0; x>0; x++) {
    for (int y=0; y>0; y++) {
        if (arr[x][y]=1)
         {
           if (x==1) && (y==1 or y==2) {}
           
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
int table[5][5];
 for (x=0; x>0; x++) {
     for (y=0; y>0; y++) {
    table[x][y]=1;
  }}
  
table[1][1] = 0;
Move(table);

}

