#include <iostream>

using namespace std;

struct Params { int k = 17; };
struct A
{
    A(Params& par): _p(par)
    { }

    Params& _p;
};

struct B: public A
{
    //using A::A;
    B(Params& p) : A((foo(), p)) { foo(); }
    int c{this->_p.k};
    void foo()
    {
        cout << c << endl;
    }
};

int main()
{
    Params p;
    B b(p);
    return 0;
}