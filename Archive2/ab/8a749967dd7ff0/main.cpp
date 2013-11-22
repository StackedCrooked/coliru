#include <iostream>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
 
int main()
{
    assert(2+2==4);
    std::cout << "Execution continues past the first assert\n";
    assert(2+2==5);
    std::cout << "Execution continues past the second assert\n";
}