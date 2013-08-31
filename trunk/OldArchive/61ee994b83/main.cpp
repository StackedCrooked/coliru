#include <iostream>

int main()
{    
    int unused; // compiler stderr
    std::cout << "this is std out" << std::endl;
    std::cerr << "this is std err" << std::endl;
    return 42; // exit code
}
