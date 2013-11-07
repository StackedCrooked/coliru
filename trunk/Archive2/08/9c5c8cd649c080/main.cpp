#include <iostream>
using namespace std;

struct X
{
    template<typename F> auto operator()(F f)
    {
        return f(1, 2);
    }
} x;

int sum(int x, int y)
{
    return x + y;
}

template<typename F, typename G>
auto apply(F f, G g)
{
    return f(g);
}

int main()
{
    cout << apply(x, sum) << endl;
}
