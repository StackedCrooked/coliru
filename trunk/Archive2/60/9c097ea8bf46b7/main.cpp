#include <iostream>

int main()
{
    int a = 1;
    int b = 2;
    
    int* aa = new (&a) int;
    int* bb = new (&b) int(); // value-initialization
    
    std::cout << *aa << ' ' << *bb << std::endl;
}
