#include <iostream>


long f(int i){return i;}
int f(long i){return -i;}

int main()
{
    for(int i=-10; i<10; i=i+3)
      std::cout << f(f(i)) << "\n";
}