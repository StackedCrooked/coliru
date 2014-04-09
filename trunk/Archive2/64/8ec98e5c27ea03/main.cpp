#include <memory>
#include <iostream>

struct Base           { ~Base()    { std::cout << __FUNCTION__ << "\n"; } };
struct Derived : Base { ~Derived() { std::cout << __FUNCTION__ << "\n"; } };

using base_ptr    = std::unique_ptr<Base>;
using derived_ptr = std::unique_ptr<Derived>;

int main()
{
    {
        derived_ptr d(new Derived);
        base_ptr oops(std::move(d)); // best not, this is the problem case
    }

    {
        derived_ptr d(new Derived);
        derived_ptr ok(std::move(d)); // this could be the case for your pimpls, many class members etc.
    }

}
