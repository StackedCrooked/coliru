#include <iostream>

template <typename F, typename G>
auto compose(F f, G g)
{
    return [=] (auto x) { return g(f(x)); };
}

int f(std::string s) { return std::stol(s); }
std::string g(int i) { return std::to_string(i); }

int main()
{
    auto h = compose(f, g);
    std::cout << h("123") << std::endl;
    return 0;
}