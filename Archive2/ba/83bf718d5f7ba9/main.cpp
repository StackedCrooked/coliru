#include <memory>

using std::shared_ptr;
using std::make_shared;

template <typename T>
class A
{
public:
    // ...
    void do_something();
};

template <typename T>
void A<T>::do_something()
{
    // ...
}

struct X { int x; };
struct Y { float x; float y; };

typedef A<X> axe;
typedef A<Y> aye;
typedef shared_ptr<axe> axe_ptr;
typedef shared_ptr<aye> aye_ptr;

class B
{
public:
    B();
    // ...
    void do_other(const axe_ptr&);
};

B::B()
{
    axe_ptr u = make_shared<axe>();
    do_other(u);
}

void B::do_other(const axe_ptr& b)
{
    b->do_something();
}

int main() {
    B b;
}