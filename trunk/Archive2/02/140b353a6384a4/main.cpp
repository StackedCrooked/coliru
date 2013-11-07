#include <iostream>
#include <iomanip>

int main()
{
    for(int i = 33; i < 127; i++) {
        std::cout << "ASCII code: " << std::setw(3) << std::setfill('0') << i << ", character: " << (char)i << std::endl;
    }
    
    return 0;
}
