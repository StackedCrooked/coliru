#include <iostream>

int called_once()
{
    std::cout << "1";
    
    return 0;
}

void call()
{
    static int x = called_once();
    (void)x;
}

int main()
{
   call();
   call();
   call();
}