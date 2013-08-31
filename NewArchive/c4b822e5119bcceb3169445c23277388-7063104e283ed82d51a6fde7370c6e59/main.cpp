#include <iostream>

struct Foo {
    void operator()() const && { std::cout << "hey!\n"; }
};

template<typename F>
void call(F&& f)
{
    (std::forward<F>(f))();
}

int main()
{
    call(Foo());
}