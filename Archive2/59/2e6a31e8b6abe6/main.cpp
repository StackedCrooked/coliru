#include <iostream>
 
struct D {
 
    D() {};
 
    D(const D& other) = delete;
 
    D(D&& other) {
        std::cout << "call D move constructor... \n";
    }
};
 
int main()
{
    try {
        throw D();
    } catch(D const& d)
    {
        
    }
}