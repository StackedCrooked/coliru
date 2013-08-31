#include <unistd.h>
#include <iostream>
#include <ctime>

int main()
{
    for (int i = 0; i != 6; ++i) {
        std::cout << i << std::endl;
        sleep(1);
    }
}//abcdef122abaaaaaaaaaaaaaaaaa