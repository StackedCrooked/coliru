#include <iostream>
#include <memory>

void doit(const std::function<void()>& f) {
    f();
}

int main()
{
    std::unique_ptr<int> p(new int(5));
    std::function<void()> f{std::move([p = std::move(p)]{
        std::cout << *p << std::endl;
    })};
    doit(f);
}
