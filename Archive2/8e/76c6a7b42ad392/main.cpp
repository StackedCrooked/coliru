#include <iostream>
#include <iomanip> 


int main()
{
    double d = 20001499920014999;
    std::cout << std::setprecision(20);
    std::cout << d << std::endl;    // output: 20001499920015000
    d = 2001499920014999;
    std::cout << d << std::endl;    // output: 2001499920014999
    
    double d1 = 0.1, d2 = 0.1, d3 = 0.1, d4 = 0.3;
    double d0 = d1 + d2 + d3 - d4;  // 0.1 + 0.1 + 0.1 - 0.3
    std::cout << d1 << std::endl;  // output: 0.10000000000000000555
    std::cout << d0 << std::endl;  // output: 5.5511151231257827021e-17
    
    return 0;
}
