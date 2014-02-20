#include <iostream>
#include <memory>

void fnRef(std::shared_ptr<int>& ptr)
{
    auto lambda = [=]() { std::cout << ptr.use_count() << ':' << __PRETTY_FUNCTION__ << '\n'; };
    lambda();
}

void fnVal(std::shared_ptr<int> ptr)
{
    auto lambda = [=]() { std::cout << ptr.use_count() << ':' << __PRETTY_FUNCTION__ << '\n'; };
    lambda();
}

int main()
{
    std::shared_ptr<int> ptr(new int);
    for (int i=0; i<10; ++i)
        fnVal(ptr);
    std::cout << '\n';

    for (int i=0; i<10; ++i)
        fnRef(ptr);

    return 0;
}
