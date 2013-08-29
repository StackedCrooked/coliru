#include <utility>
#include <tuple>

template<class Tuple>
struct foo
{
    Tuple t;
    foo(Tuple &&t) : t(std::move(t)) { }
};

template<class... Args>
using ForwardedTuple = decltype(std::forward_as_tuple(std::forward<Args>(std::declval<Args>())...));

template<class... Args>
foo<ForwardedTuple<Args...>> make_foo(Args&&... args)
{
    return {std::forward_as_tuple(std::forward<Args>(args)...)};
}

template<class... Args>
auto make_foo2(Args&& ...args) ->
    decltype(foo<decltype(std::forward_as_tuple(std::forward<Args>(args)...))>(std::forward_as_tuple(std::forward<Args>(args)...)))
{
    return foo<decltype(std::forward_as_tuple(std::forward<Args>(args)...))>(std::forward_as_tuple(std::forward<Args>(args)...));
}

int main()
{
    make_foo(1 + 1);

    make_foo2(1 + 1);
}
