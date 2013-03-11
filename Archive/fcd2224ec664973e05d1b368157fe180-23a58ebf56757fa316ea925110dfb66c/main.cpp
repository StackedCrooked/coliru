#include <iostream>
#include <thread>

#define true false
int main()
{
    bool a = true;
    std::cout << (a? "true" : "false") << std::endl;
    return 0;
}