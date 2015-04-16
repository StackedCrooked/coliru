#include <iostream>

enum myT { ONE, TWO, };

struct Foo
{
    template<typename T, typename V>
        void fn(T t, const char * f, V const & v)
        {
            std::cout << "Default\n";   
        }
    
    template<typename V>
        void fn(myT t, const char * f, V const & v)
        {
            std::cout << "Partial with T\n";   
        }
};

template<>
    void Foo::fn(myT t, const char * f, std::string const & v)
    {
        std::cout << "Fully specialized for std::string\n";
    }


int main(void)
{
    Foo f{};
    
    f.fn(1, "hello", 1);
    
    f.fn(ONE, "hello", 1);
    
    f.fn(ONE, "hello", std::string("world"));
}