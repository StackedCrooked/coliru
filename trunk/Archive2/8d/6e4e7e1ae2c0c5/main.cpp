#include <memory>

template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&& ...args) {
    return std::unique_ptr<T>(new T{std::forward<Args>(args)...});
}

struct S {
    template<class... Args>
    static std::unique_ptr<S> create(Args&&... args) {
        return make_unique<S>(std::forward<Args>(args)...);
    }
private: // if I remove this line, then the compilation is OK
    S(int) {}
    S() = default;
};

int main() {
    auto s1 = S::create(); // OK
    auto s2 = S::create(0); // Compilation error
}