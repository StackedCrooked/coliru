#include <utility>

namespace detail {
template <unsigned I>
struct priority_tag : priority_tag<I-1> {};
template <> struct priority_tag<0> {};

// High priority overload.
// If f is callable with zero args, return f()
template <typename F>
auto curry(F&& f, priority_tag<1>) -> decltype(std::forward<F>(f)()) {
    return std::forward<F>(f)();
}

// Low priority overload.
// Return a partial application
template <typename F>
auto curry(F&& f, priority_tag<0>) {
    return [f](auto&& t) {
        return curry([f,t=std::forward<decltype(t)>(t)](auto&&...args) ->
          decltype(f(t, std::forward<decltype(args)>(args)...)) {
            return f(t, std::forward<decltype(args)>(args)...);
        }, priority_tag<1>{});
    };
}
} // namespace detail

// Dispatch to the implementation overload set in namespace detail.
template <typename F>
auto curry(F&& f) {
    return detail::curry(std::forward<F>(f), detail::priority_tag<1>{});
}

template <typename F>
class partial_application {
    F f_;
public:
    template <typename T>
    explicit partial_application(T&& f) :
        f_(std::forward<T>(f)) {}

    auto operator()() { return f_(); }

    template <typename T>
    auto operator()(T&&);
};

template <typename F>
auto curry_explicit(F&& f) {
    return partial_application<F>{std::forward<F>(f)};
}

template <typename F>
template <typename T>
auto partial_application<F>::operator()(T&& t) {
    return curry_explicit([f=f_,t=std::forward<T>(t)](auto&&...args) ->
      decltype(f_(t, std::forward<decltype(args)>(args)...)) {
        return f(t, std::forward<decltype(args)>(args)...);
    });
}

#include <iostream>
#include <string>

void foo(int) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void foo(int,int) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void foo(std::string const&, double) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

static struct {
  template<class...Args>
  auto operator()(Args&&...args)const
  -> decltype(foo(std::forward<Args>(args)...))
    { return (foo(std::forward<Args>(args)...));}
} call_foo;

auto bar = [](auto&&...args){
    std::cout << __PRETTY_FUNCTION__ << ":\n";
    (void)std::initializer_list<int>{
        (void(std::cout << "  " << args << '\n'), 0)...
    };
};

int main() {
    curry(call_foo)(42);
    curry(call_foo)("foo")(12);
    curry([]{ std::cout << __PRETTY_FUNCTION__ << '\n'; });
    curry([](auto&& t){ std::cout << __PRETTY_FUNCTION__ << ": " << std::forward<decltype(t)>(t) << '\n'; })(42);
    curry_explicit(call_foo)(42)();
    curry_explicit(call_foo)(42)(13)();
    curry_explicit(bar)(12);
    curry_explicit(bar)(12)("foo")(11)(); // (std::string("bar"))();
    curry_explicit(bar)(12)("foo")(11)(std::string("bar"))();
}
