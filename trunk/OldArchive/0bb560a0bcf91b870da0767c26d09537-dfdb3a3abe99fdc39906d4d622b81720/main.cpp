#include <iostream>
#include <memory>
#include <tbb/concurrent_queue.h>
#include <thread>

template<typename T>
class chan {
public:
    chan()
        : queue{std::make_shared<tbb::concurrent_bounded_queue<T>>()} { }

    T receive() {
        T x;
        queue->pop(x);
        return x;
    }

    void send(T const& x) {
        queue->push(x);
    }

private:
    std::shared_ptr<tbb::concurrent_bounded_queue<T>> queue;
};

void foo(chan<int> channel) {
    for (;;) {
        auto x = channel.receive();
        if (x == -1) {
            break;
        }
        std::cout << x << '\n';
    }
}

void bar(chan<int> channel) {
    for (int i = 0; i < 10; ++i) {
        channel.send(i);
    }
    channel.send(-1);
}

int main() {
    chan<int> channel;
    
    std::thread a{&foo, channel};
    std::thread b{&bar, channel};
    
    a.join();
    b.join();
}
