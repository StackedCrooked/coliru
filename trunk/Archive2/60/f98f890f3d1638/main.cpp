#include <iostream>
#include <functional>

int main()
{
    int bucky[5];
    int *bp0 = &bucky[0];
    int *bp1 = &bucky[1];
    int *bp2 = &bucky[2];

    std::cout<<"bp0 is at memory address:"<<bp0<<std::endl;
    std::cout<<"bp1 is at memory address:"<<bp1<<std::endl;
    std::cout<<"bp2 is at memory address:"<<bp2<<std::endl;
    return 0;
}