#include <iostream>

int main()
{
int i = 1;
    int j = 5;
    while(j > 0)
    {
        std::cout << i*i << " ";
        
        if(i == j)
        {
            i = 1;
            --j;
            std::cout << "\n";
        }else
        {
            ++i;
        }
    }
}