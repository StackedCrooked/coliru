#include <iostream>

int main()
{
    int count = 0;
    for (int i = 1; i < 1000000; ++i)
        if (i % 4 != 0 && i % 6 != 0)
            ++count;
    std::cout << count;
}
