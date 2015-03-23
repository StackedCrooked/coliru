#include <iostream>
#include <type_traits>
using namespace std;

template <int M, int N, typename Specialization, typename... Rest>
class Test
{
    static_assert(std::is_same<Specialization, void>::value, "Don't use Test directly. Use TestHelper instead.");
    public:
    void foo(){cout << "Primary template." << endl;}
};

template <int M, int N, typename... Rest>
class Test<M, N, enable_if_t<N==M-1>, Rest...>
{
    public:
    void foo(){cout << "Specialization." << endl;}
};

template <int M, int N, typename... Rest>
using TestHelper = Test<M, N, void, Rest...>;

int main()
{
    TestHelper<5,10, int, double, char>().foo();
    TestHelper<5,4, int, double, char>().foo();
    return 0;
}