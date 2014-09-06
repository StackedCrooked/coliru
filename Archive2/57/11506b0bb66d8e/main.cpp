#include <memory>

class X { };

class Y : public X { };

std::unique_ptr<X> foo()
{
    auto y = std::make_unique<Y>();
    // Do something with y...
    return y;
}

int main()
{
}