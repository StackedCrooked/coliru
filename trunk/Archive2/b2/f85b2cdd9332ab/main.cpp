#include <iostream>

class foo
{
    public:
        struct foofoo {
            int number;
        };
};

class bar : public foo
{
    public:
        foo::foofoo foobar;
};
int main()
{
    bar b;
    b.foobar.number = 10;
    
    std::cout << b.foobar.number;
}
