#include <iostream>

enum myT { ONE, TWO, };

struct Foo
{
    template<typename T, typename V>
        void fn(T t, V const & v)
        {
            std::cout << "Default\n";   
        }
};



template<>
    void Foo::fn(myT t, std::string const & v)
    {
        std::cout << "Fully specialized for std::string\n";
    }


//// :(
template<>
template<typename V>
    void Foo::fn(myT t, V const & v)
    {
        std::cout << "Partial with T\n";   
    }



int main(void)
{
    Foo f{};
    
    f.fn(1, 1);
    
    f.fn(ONE, 1);
    
    f.fn(ONE, std::string("world"));
}