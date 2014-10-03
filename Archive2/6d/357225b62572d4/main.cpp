#include <functional>
#include <utility>

template<typename Signature>
class bound_function;

template<typename Ret, typename... Args>
class bound_function<Ret(Args...)> {
public:
    template<typename F>
    explicit bound_function(F function_) : function(std::move(function_)) { }

    (*operator Ret() const)(Args...) {
        
    }

private:
    std::function<Ret(Args...)> function;
};

int main() {
    return 0;
}
