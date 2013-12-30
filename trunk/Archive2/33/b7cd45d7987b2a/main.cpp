#include <iostream>
#include <memory>

void doit(std::function<void()> f) {
    f();
}

int main()
{
    auto f = [p = std::unique_ptr<int>(new int(5))] () {
        std::cout << *p << std::endl;
    };
    doit(std::ref(f));
}
