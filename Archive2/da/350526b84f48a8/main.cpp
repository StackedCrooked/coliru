#include <iostream>
#include <thread>
 
int main() {
    for (auto i=0; i<20; ++i)
    {
        if (i%3 == 0)
        {
            std::cout << i << std::endl;
            
        }
    }
}