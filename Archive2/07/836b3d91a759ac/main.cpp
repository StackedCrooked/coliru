#include <iostream>

class foo
{
public:
    foo() { std::cout << "default" << std::endl; }
    foo(const foo &) { std::cout << "copy" << std::endl; }
    foo(foo &&) { std::cout << "move" << std::endl; }
};

foo f1()
{
    foo f;
    return f;
}

foo f2()
{
    foo f;
    return std::move(f);
}

int main()
{
    foo foo1 = f1();
    std::cout << "---" << std::endl;
    foo foo2 = f2();
    std::cout << "===" << std::endl;
}
