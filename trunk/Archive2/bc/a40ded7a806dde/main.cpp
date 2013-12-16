#include <iostream>
using namespace std;

template <typename U> using id = U;

template <template <typename...> class F, typename... T>
using apply1 = F <T...>;

template <template <typename...> class F>
struct apply2
{
    template <typename... T>
    using map = F <T...>;
};

int main()
{
    cout << apply1 <id, int>() << endl;
    cout << apply2 <id>::map <int>() << endl;
}