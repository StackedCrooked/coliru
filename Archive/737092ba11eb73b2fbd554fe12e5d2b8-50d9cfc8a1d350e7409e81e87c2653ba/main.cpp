#include <functional>

struct foo {
    template<typename T>
    T operator()(T value)
    { return value; }
};

int main()
{
    std::function<double(double)> f = foo {};
    return f(4);
}