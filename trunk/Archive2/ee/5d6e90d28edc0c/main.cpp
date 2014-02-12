#include <iostream>
#include <string>
#include <vector>


int main()
{   
    if ( NULL == nullptr )
        std::cout << "YUP" << std::endl;
        
    if ( NULL != nullptr )
        std::cout << "NOPE" << std::endl;
}
