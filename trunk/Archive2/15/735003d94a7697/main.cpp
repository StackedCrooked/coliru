#include <iostream>
#include <type_traits>

template< typename Func >
class Wrapper {
    public:
        template < typename = typename std::enable_if< std::is_void<decltype(Func())>::value>::type >
        static void exec(Func f) {
            std::cout << "I'm void" << std::endl;
            f();
            // other stuff
            return;
        }
        
        template < typename = typename std::enable_if< false >::type >
        static auto exec(Func f) -> decltype(f()) {
            std::cout << "I'm not void" << std::endl;
            auto result = f();
            // other stuff
            return result;
        }

};

int blah()
{
    return 2; 
}

void foo()
{
    std::cout << "Bleh" << std::endl;
}

int main(int argc, char* argv[])
{
    std::cout << Wrapper<decltype(blah)>::exec(blah) << std::endl;
    Wrapper<decltype(foo)>::exec(foo);
    
    return 0;
}
