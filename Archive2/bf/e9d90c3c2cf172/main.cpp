#include <iostream>
#include <cstdio>
#include <vector>

int main ()
{
    int n = 29; 
    if (n < 0 || n > 29) {
        return 1; 
    }
          
    std::vector<int> g (n);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            g[i] = 0;
            std::cout << i << " = " << g[i]; 
        }
        else if (i == 1 || i == 2) {
            g[i] = 1;
            std::cout << i << " = " << g[i];
        }
        else {
            g[i] = (g[i - 3] + g[i - 2] + g[i - 1]);
            std::cout << i << " = " << g[i];
        }
        
        std::cout << std::endl;
    }
    return 0;
}