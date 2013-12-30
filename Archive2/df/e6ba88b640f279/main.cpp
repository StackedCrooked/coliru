#include <iostream>
#include <memory>

void doit(std::function<void()> f) {
    f();
}

int main()
{
    std::unique_ptr<int> p(new int(5));
    auto f = [p = std::move(p)] () { std::cout << *p << std::endl; };
    doit(std::ref(f));
}
