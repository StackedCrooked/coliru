#include <iostream>
#include <fstream>
 
int main()
{
    std::ofstream ofs;
    ofs << 1 << std::endl;
    
    std::cout << ofs.good() << std::endl;
}