#include <iostream>
 
int main(int argc, char** argv)
{
    // the compiler hates me :(
    // std::cout << "Hi, I'm " + argv[0] << '\n';
    // This works though
    std::cout << "Hi, I'm " << argv[0] << '\n';
}