#include <iostream>

const int foo()
{
    return 3;
}

int main()
{
    int check;
    check=foo();
    std::cout<<"before:"<<check<<std::endl;
    check=1;
    std::cout<<"after:"<<check<<std::endl;
    return 0;   
}