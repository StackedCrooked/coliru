#include <tuple>

struct Base {};

class C
{
private:
    struct Derived : Base {};
    std::tuple<Derived, Derived> d;
    
public:
    std::tuple<Base&, Base&> leak()
    {
        return d;
    }
};

int main()
{
    C c;
    auto x = c.leak();
}