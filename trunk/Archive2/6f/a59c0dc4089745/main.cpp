#include <iostream>

int main()
{
    std::cout << "GCC version is: " << __GNUC__ // major version
              << '.' << __GNUC_MINOR__ // minor version
              << '.' << __GNUC_PATCHLEVEL__ // patch 
              << '\n' ;
}
