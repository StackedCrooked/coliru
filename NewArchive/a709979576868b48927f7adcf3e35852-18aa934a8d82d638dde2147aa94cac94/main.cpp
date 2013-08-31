#include <iostream>
#include <thread>

namespace DKIM {
    void incBy1(int& someNum);
}

int main()
{

    int someNum = 23;
    
    DKIM::incBy1(someNum);
    
    std::cout << someNum << std::endl;

}

void DKIM::incBy1(int& someNum) {
    someNum++;
}

