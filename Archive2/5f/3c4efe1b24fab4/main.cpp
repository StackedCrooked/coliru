#include <iostream>
#include <stdint.h>

int main()
{
    char c, next;
    int count = 1;
    std::cin.read(&c, 1);
    while (std::cin.read(&next, 1))
    {
        if (next == c)
        {
            count++;
        }
        else
        {
            std::cout << count << c;
            c = next;
            count = 1;
        }
    }
    std::cout << next;
}