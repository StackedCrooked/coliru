#include <iostream>


struct A
{
    template<typename ... Args>
    A(Args && ... ) { std::cout << "Being used for copy!" << std::endl; }
};

int main(int argc, char *argv[])
{
    A const a{};
    A b(a);
    
    (void)b;
}
