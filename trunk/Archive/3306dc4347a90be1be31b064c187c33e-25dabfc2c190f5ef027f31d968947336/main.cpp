#include <iostream>
#include <type_traits>

class Myclass{
private:
        int i;
public:
    template<typename U>
    Myclass(U& lvalue):i(lvalue)
    {
        std::cout << i <<" template light reference" << std::endl;
        i++;
    }

    template<typename U,
        typename std::enable_if<
            !std::is_reference<U>::value
            >::type* = nullptr>
    Myclass(U&& rvalue):i(rvalue)
    {
        std::cout << i <<" template right reference" << std::endl;
        i++;
    }
};

int main(int argc,char*argv[])
{
    Myclass a(0);

    int x = 42;
    Myclass b(x);

    Myclass c(2);
}
