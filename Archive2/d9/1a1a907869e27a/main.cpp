#include <cassert>

struct P {
    P() {}
    typedef int P::* Bool;
    operator Bool() const { return 0; }
};

struct P2 {
    P2() {}
    typedef int P2::* Bool;
    operator P2*() const { return 0; }
};

char test_helper(void*);
double test_helper(...);

int main()
{
    P p;
    assert(sizeof(test_helper(p)) > 1);
    
    P2 p2;
    assert(sizeof(test_helper(p2)) == 1);
}
