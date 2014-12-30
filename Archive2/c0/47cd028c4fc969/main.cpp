#include <tuple>

template<typename T>
struct identity_t
{
    using type = T;
};
template<typename T>
using non_deduced_context = typename identity_t<T>::type;

template<typename ...ARGS1, typename ...ARGS2>
void foo(const std::tuple<ARGS1...> &, const std::tuple<ARGS2...> &, non_deduced_context<void (*)(ARGS1..., ARGS2...)>)
{
    //call function
}

void bar(int, bool, double, void*, float)
{
}

int main()
{
    std::tuple<int, bool> tuple1(0, false);
    std::tuple<double, void*, float> tuple2(0.0, nullptr, 0.0f);
    foo(tuple1, tuple2, &bar);
    return 0;
}