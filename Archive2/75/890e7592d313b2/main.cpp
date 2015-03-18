#include <iostream>
#include <memory>

template <typename Derived>
struct silly {
    template <typename... Ts>
    static std::shared_ptr<Derived>
    create(Ts&&... ts) {
        return std::make_shared<Derived>(std::forward<Ts>(ts)...);
    }
};

struct object : silly<object> {
    object(int i) {
        std::cout << i << '\n';
    }
};

int
main() {
    auto o = object::create(5);
}
