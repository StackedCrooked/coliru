#include <iostream>
#include <string>
#include <vector>

int * foo(){
    int y=12;
    return &y;
}
void increment(int*& i) { i++; };
using namespace std;
int main()
{
    int x = 4;
    int y = 100;
    int &r = x;
    r = y;
    r++;
    
    std::cout << r << std::endl;
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    
    int *xp = foo();
    
    std::cout << *xp << std::endl;
 int* i = 0;
  cout << "i = " << i << endl;
  increment(i);
  cout << "i = " << i << endl;
     
}
