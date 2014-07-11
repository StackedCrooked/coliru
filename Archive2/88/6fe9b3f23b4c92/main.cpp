#include <iostream>

int main()
{
int *tmp = new int;
    std::cout << tmp << std::endl;
    int *tmp2 = new int;
    std::cout << tmp2 << std::endl;
    delete tmp;         // если поменять местами то        
    delete tmp2;        // адрес temp3 изменится
    int *tmp3 = new int;
    std::cout << tmp3 << std::endl;
    delete tmp3;
}