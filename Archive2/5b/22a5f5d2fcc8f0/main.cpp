#include <iostream>

namespace one {

    template<typename... Args>
        void write(Args const&... args) 
        {
            std::initializer_list<int> l { (std::cout << args << ' ', 0)... };
            (void)l;
            std::cout << std::endl;
        }
}


namespace two 
{
    struct Foo
    {
        constexpr static char* C = (char *)"hello";
    };
}

int main(void)
{
    one::write("test", 1, 2, 'a');
    one::write("test2", two::Foo::C);
}
