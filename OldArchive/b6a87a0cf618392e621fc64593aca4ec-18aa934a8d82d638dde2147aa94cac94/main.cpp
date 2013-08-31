#include <unistd.h>
#include <iostream>
#include <ctime>

int main()
{
    for (int i = 0; i != 5; ++i) {
        std::cout << i << std::endl;
        std::sleep(1);
    }
}//abcdef122abaaaaaaaaa