#include <unistd.h>
#include <iostream>
#include <ctime>

int main()
{
    for (int i = 0; i != 5; ++i) {
        std::cout << i << std::endl;
        sleep(1);
    }
}//abcdef122abaaaaaaaaaaaaaaaaa