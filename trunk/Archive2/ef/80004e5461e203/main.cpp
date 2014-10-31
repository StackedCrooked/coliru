#include <utility>

// This conditionally forwards a member of the type T
// it is a helper for the function below
template<class T>
struct forward_member_t {
    template<class U>
    decltype(auto) operator()(U&& u)const { return std::move(u); }
};
template<class T>
struct forward_member_t<T&&>:forward_member_t<T>{};

template<class T>
struct forward_member_t<T&> {
    template<class U>
    U&& operator()(U&& u)const { return std::forward<U>(u); }
};

// Use:
// forward_member<T>(t.foo) will move foo if T&& is an rvalue reference
// If the U&& passed in is an rvalue reference, it will also return U&&
template<class T, class U>
auto forward_member( U&& u ) {
    return forward_member_t<T>{}(std::forward<U>(u));
}

struct foo {
    int foo;
};

static_assert(std::is_same<decltype(forward_member<foo>(std::declval<foo>().foo)), decltype(std::forward<foo>(std::declval<foo>()).foo)>(), "");
static_assert(std::is_same<decltype(forward_member<foo&>(std::declval<foo&>().foo)), decltype(std::forward<foo&>(std::declval<foo&>()).foo)>(), "");
static_assert(std::is_same<decltype(forward_member<foo const&>(std::declval<foo const&>().foo)), decltype(std::forward<foo const&>(std::declval<foo const&>()).foo)>(), "");
static_assert(std::is_same<decltype(forward_member<foo const>(std::declval<foo const>().foo)), decltype(std::forward<foo const>(std::declval<foo const>()).foo)>(), "");
