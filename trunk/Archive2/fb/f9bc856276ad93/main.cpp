#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct IDereferencable
{
    virtual int dereference() const = 0;
protected:
    ~IDereferencable() = default;
};

template<typename Dereferencable>
struct ConcreteDereferencable : IDereferencable
{
    Dereferencable x;
    ConcreteDereferencable(Dereferencable x) : x(x) {}
    int dereference() const override
    {
        return *x;
    }
};

template<typename Dereferencable>
auto make_wrapper(Dereferencable x)
{
    return ConcreteDereferencable<Dereferencable>{x};
}

void test(const IDereferencable &x)
{
    cout << x.dereference() << endl;
}

int main()
{
    int a = 1;
    vector<int> b{3, 4};
    set<int> c{5, 6};

    auto x = make_wrapper(b.begin());

    test(make_wrapper(&a));
    test(x);
    b[0] = 111;
    test(x);
    test(make_wrapper(c.begin()));
}