#include <memory>
#include <iostream>

template<typename F>
struct OptionalDeleter final {
    explicit OptionalDeleter(F&& f) : _f(std::forward<F>(f)) {}

    template <typename... Ts>
        void operator()(Ts&&... args) const { _f(std::forward<Ts>(args)...); }

    void operator()(std::nullptr_t)   const { std::cout << "Empty, not deleting\n"; }
  private:
    F _f;
};

template <typename F>
OptionalDeleter<F> make_optional_deleter(F&& f) { return OptionalDeleter<F>(std::forward<F>(f)); }

int main() {
    auto d = make_optional_deleter([](void*){std::cout << "Deleting\n";});
    
    using namespace std;
    {
        shared_ptr<int> empty(std::nullptr_t{}, d);
    } // deleter not called, empty

    {
        shared_ptr<int> thing(static_cast<int*>(nullptr), d);
    } // deleter called, thing not empty
}
