#include <iostream>

template<typename Type>
class Test {
public:

    Test();
    ~Test() 
    {
        std::cout << "Default Dtor called." << std::endl;
    }

    void print();
};

//! These should go either in the class declaration or in a separate ipp/inl file.
//! You can put these in a .cpp if you use extern templates, but they might not be
//! supported on your compiler.
struct Type_1{};
struct Type_2{};

Test<Type_1>::Test()
{
    std::cout << "Type_1 Ctor called" << std::endl;
}

Test<Type_1>::~Test()
{
    std::cout << "Type_1 Dtor called" << std::endl;
}

Test<Type_2>::Test()
{
    std::cout << "Type_2 Ctor called" << std::endl;
}

int main()
{
    {
        Test<Type_1> t1;
    }

    {
        Test<Type_2> t2;
    }
}