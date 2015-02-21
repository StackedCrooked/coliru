#include <iostream>
#include <vector>
#include <type_traits>
#include <functional>
#include <utility>
#include <tuple>
using namespace std;

/* You can ignore the && and the forward<>(). Please look up perfect forwarding and universal references for more on them. They aren't relevant to this problem.
 * Invoke knows, through template argument deduction, the number of arguments, say N, that "func" needs. So you simply need to pick the first N arguments from PassedArgs... args.
 * However, since there is so little that C++ allows you to do with parameter packs, we resort to this "InvokeHelper" + "index_sequence" trick. std::index_sequence<size_t...> is a variadic template
 * which acts like a compile-time list of indices. Since you only care about the 0-th, 1-st, 2nd,..., (N-1)-th elements of PassedArgs...args, you first construct an std::index_sequence
 * with its (non-type) template arguments being 0, 1, ..., N-1. std::index_sequence_for helps you do that. With this extract level of template argument deduction(Invoke -> InvokeHelper)
 * we manage to get an appropriate parameter pack Inds... and use that in InvokeHelper.
 */
 
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
