#include <iostream>

#define mycout std::cout <<  __FILE__  << "(" << __LINE__ << ") "
#define cout mycout

int main()
{
    cout << "Hello";
}