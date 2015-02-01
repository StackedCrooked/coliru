#include <utility>
#include <type_traits>

template<typename Functor>
struct pipeable : public Functor {
    template<typename... Args>
    pipeable(Args&&... args): Functor(std::forward<Args>(args)...) {}
};

// represents an actual expression, expression<f, g> -> g(f())
// note that this is executed left to right not right to left
template<typename First, typename Second>
struct expression {
private:
    First lhs;
    Second rhs;
public:
    expression(First lhs, Second rhs): lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    template<typename... Args>
    auto operator()(Args&&... args) const -> decltype(rhs(lhs(std::forward<Args>(args)...))) {
        return rhs(lhs(std::forward<Args>(args)...));
    }
};

template<typename T>
struct is_pipeable : std::false_type {};

template<typename T>
struct is_pipeable<pipeable<T>> : std::true_type {};

template<typename T, typename U>
struct is_pipeable<expression<T, U>> : std::true_type {};

// x | f | g | h
// (((x | f) | g) | h)
// expression<expression<expression<x, f>, g>, h>

template<typename First, typename Second, typename Result = expression<First, Second>,
         typename std::enable_if<is_pipeable<First>::value and is_pipeable<Second>::value, int>::type = 0>
inline Result operator|(const First& lhs, const Second& rhs) {
    return Result{lhs, rhs};
}

template<typename Function>
inline pipeable<Function> make_pipe(const Function& func) {
    return pipeable<Function>{func};
}

#include <iostream>

int main() {
    auto f = make_pipe([](int x) { return x + 10; });
    auto g = make_pipe([](int y) { return y * 20; });
    auto h = make_pipe([](int z) { return z / 5; });
    auto test = f | g | h;
    std::cout << test(20) << '\n';
}
