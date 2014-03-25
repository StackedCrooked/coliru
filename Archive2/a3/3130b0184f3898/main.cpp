#include <exception>

// error: member function 'fun' not viable: 'this' argument has type 'const Const', but function is not marked const
class Const
{
    void fun()       {}
public:
    void gun() const { fun(); }
};

// error: constexpr function never produces a constant expression [-Winvalid-constexpr]
class ConstExpr
{
    static           int fun() { return 0; }
public:
    static constexpr int gun() { return fun(); }
};

class NoExcept
{
    void fun()          { throw std::exception(); }
public:
    void gun() noexcept { fun(); }
};

int main() {}
