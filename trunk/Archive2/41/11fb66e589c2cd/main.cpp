#include <iostream>
#include <type_traits>

enum struct C { x = 5 };

enum D 
{ 
    y = 0, 
    x = static_cast<std::underlying_type<C>::type>(C::x) 
};

int main(){ }
