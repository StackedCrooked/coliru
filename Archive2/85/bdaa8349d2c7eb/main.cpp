#include <functional>

struct X
{
    std::function<X()> _gen;
};

int main()
{
    X x;
    x._gen = [] { return X(); };
}
