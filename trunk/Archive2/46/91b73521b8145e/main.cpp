struct foo
{
    virtual void bar() {}
};

#include <iostream>
int main()
{
    std::cout << sizeof(void*) << " : " << sizeof(&foo::bar);
}