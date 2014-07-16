#include <iostream>

void g7(int);
template<typename T> 
void f7(T x) 
{ 
    g7(x); // (1) 
} 
void g7(int) 
{
    std::cout << "g7(int)\n";
} 
template void f7<int>(int);
template void f7<int>(int);
 
int main()
{
    f7(1);
}