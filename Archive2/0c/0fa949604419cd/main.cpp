#include <iostream>

void prova(int &i){
    i = 12
};

int main()
{
    int i = 32;
    std::cout << "i:" << i << "\n";
    prova(i);
    std::cout << "i:" << i << "\n";
    return 0;
}
