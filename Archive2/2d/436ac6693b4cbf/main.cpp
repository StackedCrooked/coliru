#include <iostream>
#include <memory>


int main()
{
    typedef std::unique_ptr<int> up_int;
    up_int u{new int(3)};
    auto l = [ u{std::move(u)} ]() { std::cout << *u << std::endl;};
    l();
}
