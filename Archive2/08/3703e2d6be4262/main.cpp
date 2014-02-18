#include <memory>
#include <utility>

template <typename T, typename...Args>
inline std::unique_ptr<T> make_unique(Args&&...args) {
    return std::unique_ptr<T>{new T(std::forward<Args>(args)...)};
}

struct Variable {
    std::string name_;
    
    explicit Variable(std::string name) : name_{std::move(name)} {}
};

struct Assignment {
    std::unique_ptr<Variable> a_, b_;
    
    template <typename T, typename U>
    Assignment(T&& a, U&& b) :
      a_{make_unique<Variable>(std::forward<T>(a))},
      b_{make_unique<Variable>(std::forward<U>(b))} {}
};

auto assignment = make_unique<Assignment>("a", "b");
