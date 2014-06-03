#include <iostream>

int main(int argc, char* argv[])
{
    int i = 0;
    (i += 5).~decltype(i)();
    std::cout << i;
}
