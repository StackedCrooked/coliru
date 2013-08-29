#include <iostream>
#include <thread>

static void incBy1(int& someNum);

int main()
{

    int someNum = 23;
    
    incBy1(someNum);
    
    std::cout << someNum << std::endl;

}

void incBy1(int& someNum) {
    someNum++;
}
