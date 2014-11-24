#include <functional>
#include <iostream>
#include <vector>

template <typename> struct dynamic_overload;

template <typename R, typename... Args>
class dynamic_overload<R(Args...)> {
public:
    void
    add(std::function<bool(Args...)> const& cond, 
        std::function<R(Args...)> const& target) {
        overloads_.push_back({cond, target});
    }
    
    R
    operator () (Args&&... args) {
        for (auto const& candidate : overloads_) {
            if (candidate.condition(std::forward<Args>(args)...))
                return candidate.target(std::forward<Args>(args)...);
        }
        
        throw "Something, I don't care";
    }

private:
    struct overload {
        std::function<bool(Args...)> condition;
        std::function<R(Args...)> target;
    };
    
    std::vector<overload> overloads_;
};

int
foo_small(int x) {
    return 2 * x;
}

int
foo_big(int x) {
    return 2 + x;
}

int
main() {
    dynamic_overload<int(int)> foo;
    foo.add([] (int x) { return x < 50; }, foo_small);
    foo.add([] (int x) { return x >= 50; }, foo_big);
    
    std::cout << foo(5) << '\n'
              << foo(15) << '\n'
              << foo(55) << '\n';
}
