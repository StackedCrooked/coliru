#include <utility>

namespace detail {
template <unsigned I>
struct priority_tag : priority_tag<I-1> {};
template <> struct priority_tag<0> {};

// High priority overload.
// If f is callable with zero args, return f()
template <typename F>
constexpr auto curry(F&& f, priority_tag<1>) -> decltype(std::forward<F>(f)()) {
    return std::forward<F>(f)();
}

// Low priority overload.
// Return a partial application
template <typename F>
constexpr auto curry(F&& f, priority_tag<0>) {
    return [f](auto&& t) {
        return curry([f=f,t=std::forward<decltype(t)>(t)](auto&&...args) ->
          decltype(f(t, std::forward<decltype(args)>(args)...)) {
            return f(t, std::forward<decltype(args)>(args)...);
        }, priority_tag<1>{});
    };
}
} // namespace detail

// Dispatch to the implementation overload set in namespace detail.
template <typename F>
constexpr auto curry(F&& f) {
    return detail::curry(std::forward<F>(f), detail::priority_tag<1>{});
}

#include <iostream>
#include <string>

void foo(int) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void foo(std::string, double) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

static struct {
  template<class...Args>
  auto operator()(Args&&...args)const
  -> decltype(foo(std::forward<Args>(args)...))
    { return (foo(std::forward<Args>(args)...));}
} call_foo;

int main() {
    curry([]{ std::cout << __PRETTY_FUNCTION__ << '\n'; });
    curry([](auto&& t){ std::cout << __PRETTY_FUNCTION__ << ": " << std::forward<decltype(t)>(t) << '\n'; })(42);
    curry(call_foo)(42);
    curry(call_foo)("foo")(12);
}
