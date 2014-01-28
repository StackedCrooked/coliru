#include <cassert>
#include <functional>
#include <iostream>

#include <boost/function.hpp>
#include <boost/lockfree/queue.hpp>

int main() {
    //boost::lockfree::queue<boost::function<void(int)>> queue(50);
    boost::lockfree::queue<void (*)(int)> queue(50);
    assert(queue.is_lock_free());

    for (int j = 0; j < 50; ++j) {
        queue.push([](int i) { std::cout << i << std::endl; });
    }

    int i = 0;
    boost::function<void(int)> functor;
    while (queue.pop(functor)) {
        functor(i++);
    }
}