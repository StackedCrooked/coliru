#include <iostream>
#include <algorithm>
 
void* operator new[](std::size_t sz, char c)
{
    void* p = operator new[](sz);
    std::fill_n(reinterpret_cast<char*>(p), sz, c);
    return p;
}
 
int main()
{
    char* p = new('*') char[6];
    p[5] = '\0';
    std::cout << p << '\n';
    delete[] p;
}