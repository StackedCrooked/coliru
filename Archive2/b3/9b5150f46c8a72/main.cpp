#include <iostream>
#include <cstdlib>
 
int main(int argc, char *argv[])
{
    std::cout << "Your PATH is: " << std::getenv("PATH") << std::endl;
}