#include <string>
#include <iostream>

int main()
{
    std::string stra ; // fine, default constructed
    std::cout << "1\n" << std::flush ;
    
    std::string strb = "hello" ; // fine, default constructed with const char*
    std::cout << "2\n" << std::flush ;

    std::string str(nullptr) ; // *** error: null pointer 
    std::cout << "3\n" << std::flush ;
}
