#include <iostream>
#include <vector>

using namespace std;

void __attribute__ ((noinline)) violation(int x)
{
    cout << "Violation found at " << x << endl;
}

template<typename P, typename X>
bool all(P p, X x)
{
    return p(x);
}

template<typename P, typename X, typename ...Xs>
bool all(P p, X x, Xs... xs)
{
    return p(x) && all(p, xs...);
}

// _____________________________________________________________________________________________ //

auto conjunction = [](auto ...predicates)
{
    return [=](auto x)
    {
        return all([=](auto p){ return p(x); }, predicates...);
    };
};

void test_closure()
{
    vector<int> data(20 * 1000 * 1000);
    auto check_for_zero = conjunction
    (
        [](auto x){ return x > -1; },
        [](auto x){ return x <  1; }
    );
    for(auto x : data)
        if(!check_for_zero(x))
            violation(x);
}

void test_manual()
{
    vector<int> data(20 * 1000 * 1000);
    for(auto x : data)
        if(!(x > -1 && x < 1))
            violation(x);
}

int main()
{
    test_closure();
    test_manual();
}
