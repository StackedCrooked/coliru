
#include <iostream>

const struct default_t
{
     template<typename T>
     operator T() const {   return T{}; }
}default_;

struct VeryVeryVeryLongTypeName { int value = 100; };
struct YetAnotherVeryVeryVeryLongTypeName { int value = 1000; };

VeryVeryVeryLongTypeName f()
{
     //...
     return default_;
}

YetAnotherVeryVeryVeryLongTypeName g()
{
     //...
     return default_;
}
int main() 
{
    std::cout << f().value << std::endl;
    std::cout << g().value << std::endl;
}