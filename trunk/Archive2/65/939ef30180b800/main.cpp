#include <iostream>
#include <fstream>

int main()
{
    std::ifstream f("/tmp");
    std::cout << "Exception Flags: " << f.exceptions() << std::endl;
    if(f >> std::ws) std::cout << "This will not succeed" << std::endl;
    else std::cout << "Ok - it fails" << std::endl;
    return 0;
}