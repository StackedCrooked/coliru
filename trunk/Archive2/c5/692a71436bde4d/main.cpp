#include <iostream>

// Declare the Trait
template<class T> class Foo
{};


// Specialization for int
template<> class Foo<int>
{
public:
    using my_type = float;
};

// SPecialization for float
template<> class Foo<float>
{
public:
    using my_type = int;
};

int main()
{
    Foo<int>::my_type fvar = 0.5; // float
    
    Foo<float>::my_type ivar = 10; // int
    
    std::cout << fvar << "   " << ivar << std::endl;
    
    return 0;
}