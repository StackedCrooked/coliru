#include <utility>
#include <iostream>
#include <memory>

struct base {
    ~base() { std::cout << "base\n"; }
};

struct derived:base {
    ~derived() { std::cout << "derived\n"; }
};

    template<class T>
    using smart_unique_ptr = std::unique_ptr<T, std::function<void(void*)>>;

    template<class T, class...Args>
    smart_unique_ptr<T> make_smart_unique( Args&&... args ) {
      auto p = new T(std::forward<Args>(args)...);
      return { p, [p](void*) {delete p;} };
    }

int main() {
    smart_unique_ptr<base> ptr = make_smart_unique<derived>();
    ptr.reset();
}