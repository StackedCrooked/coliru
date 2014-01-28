#include <sstream>
#include <iostream>
#include <string>

int main()
{
    int i = 0;
    int j = 0;
    std::string userName("Bob");
    std::string password("foo");
    
    std::stringstream ss;
    ss << "INSERT INTO Login (_id,username,password,manager_id) ";
    ss << "VALUES (" << i << ","  << userName << ", " << password << "," << j << ");";
    const char* sql = ss.str().c_str();
    
    std::cout << sql << std::endl;
    
    return 0;
}
    