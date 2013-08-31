#include <unistd.h>
#include <iostream>
#include <ctime>

int main()
{
    for (int i = 0; i != 5; ++i) { std::cout << i << ": " << time(0) << std::endl; sleep(1); }
}//abcdef122abaaaaaa