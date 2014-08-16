#include <iostream>
#include <memory>

namespace xtd {
    using std::shared_ptr;

    template<class T, class... Args>
    std::enable_if_t<std::is_constructible<T, Args...>::value, shared_ptr<T>> make_shared(Args&&... args) {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<class T, class... Args>
    std::enable_if_t<!std::is_constructible<T, Args...>::value, shared_ptr<T>> make_shared(Args&&... args) {
        return shared_ptr<T>(new T{std::forward<Args>(args)...});
    }
}

template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node> next;
};

int main() {
    auto ptr = xtd::make_shared<Node<int>>(42, xtd::make_shared<Node<int>>(43, nullptr));
    std::cout << ptr->data << ' ' << ptr->next->data << '\n';
}
