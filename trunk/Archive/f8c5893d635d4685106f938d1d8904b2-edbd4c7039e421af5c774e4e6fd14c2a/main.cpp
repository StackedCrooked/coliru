#include <functional>
#include <tbb/concurrent_queue.h>
#include <thread>
#include <utility>

template<typename T>
class actor {
public:
    template<typename F>
    explicit actor(F callback)
        : thread{[&, this] { callback(*this); }}
        , queue{} { }
    
    ~actor() {
        thread.join();
    }
    
    void send(T const& message) {
        queue.push(message);
    }
    
    T receive() {
        T message;
        queue.pop(message);
        return message;
    }

private:
    std::thread thread;
    tbb::concurrent_bounded_queue<T> queue;
};

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <tuple>

int main() {
    actor<std::string> logger_actor{[] (decltype(logger_actor)& self) {
        for (;;) {
            auto message = self.receive();
            std::cout << self.receive() << '\n';
        }
    }};
    
    actor<std::tuple<actor<int>*, int, int>> random_number_generator_actor{[&] (decltype(random_number_generator_actor)& self) {
        std::mt19937 prng(std::time(nullptr));
        for (;;) {
            auto message = self.receive();
            std::uniform_int_distribution<> dis(std::get<1>(message), std::get<2>(message));
            std::get<0>(message)->send(dis(prng));
        }
    }};
    
    actor<int> main_actor{[&] (decltype(main_actor)& self) {
        for (int i = 0; i < 10; ++i) {
            random_number_generator_actor.send(std::make_tuple(&self, 0, 10));
            int x = self.receive();
            logger_actor.send(std::to_string(x));
        }
    }};
}
