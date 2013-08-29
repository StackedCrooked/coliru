#include <iostream>

struct A
{
private:
    struct B {
       int get() const { return 5; }
    };

public:
   B get() const { return B(); }
};

int main()
{
   A a;
   decltype(a.get()) b;

   std::cout << b.get() << std::endl;
}