#include <iostream>
 
int main()
{
    int i = 0;
    while (i < 10) i++;
 
    std::cout << i << '\n';
 
    int j = 2;
    while (j < 9) {
        std::cout << j << " ";
        j += 2;
    }
}