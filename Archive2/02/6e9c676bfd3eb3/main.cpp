#include <string>
#include <iostream>

void fun(std::string s)
{
    std::cout << reinterpret_cast<void*>(const_cast<char*>(s.data())) << std::endl;
}

int main()
{
    std::string s = "whatever";
    std::cout << reinterpret_cast<void*>(const_cast<char*>(s.data())) << std::endl;
    
    fun(s.data());
}