#include <iostream>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
 
int main()
{
    assert(2+2==3);
    std::cout << "Merge\n";
    //assert(2+2==5);
    //std::cout << "Execution continues past the second assert\n";
}