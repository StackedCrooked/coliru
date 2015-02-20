#include <iostream>
#include <vector>
#include <type_traits>
#include <functional>
#include <utility>
#include <tuple>
using namespace std;

template <typename Ret, typename ... FuncArgs, typename ... PassedArgs, size_t... Inds>
Ret InvokeHelper(function<Ret(FuncArgs...)>& func,  index_sequence<Inds...>, PassedArgs&&... args)
{
    static_assert(sizeof...(FuncArgs) <= sizeof...(PassedArgs), "Too few arguments passed.");
    auto args_tuple = make_tuple(forward<PassedArgs>(args)...);
    return func(get<Inds>(args_tuple)...);
}

template <typename Ret, typename ... FuncArgs, typename ... PassedArgs>
Ret Invoke(function<Ret(FuncArgs...)>& func, PassedArgs&&... args)
{
    return InvokeHelper(func, index_sequence_for<FuncArgs...>(), std::forward<PassedArgs>(args)...);
}

int main()
{
    function<void(int,int)> func = [](int a, int b){cout << a+b << endl;};
    Invoke(func, 1, 2);
    Invoke(func, 1, 2, 3);

    return 0;
}
