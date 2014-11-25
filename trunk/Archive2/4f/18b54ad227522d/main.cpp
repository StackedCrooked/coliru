#include <iostream>


int main()
{

    int i, j;
    
    j = 9;
    i = 1;
    
    while (i <= j)
    {
        for(int x = i; x <= j; x++)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        i++;
        j--;
        std::cout << "  ";
        
    }
        
    
    return 0;
}
