#include <iostream>
#include <string>
#include <vector>

int main()
{
    int numbers[5];
    int i = 0;
    for (int &n : numbers) {        
        n = i;       
        i++;
    }
    
    for (int n : numbers) {
        std::cout << n << " ";
    }
    
    return 0;
}
