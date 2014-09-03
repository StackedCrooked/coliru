
#include <functional>
#include <list>
#include <iostream>

using received_msgs_type = std::list<int>;

template<class F>
void notify_received(F&& f) {
    f();
}

int main() {
    received_msgs_type received_msgs;
    int x = 42;
    notify_received(std::bind(
        static_cast<void (received_msgs_type::*)(int const&)>(
            &received_msgs_type::push_front
        ),
        std::ref(received_msgs),
        std::cref(x)
    ));
    notify_received([&received_msgs]() {
        received_msgs.push_front(3);
    });
    std::cout << received_msgs.size() << std::endl;
    auto it = received_msgs.cbegin();
    while (it != received_msgs.cend()) {
        std::cout << *it << std::endl;
        ++it;
    }
}
