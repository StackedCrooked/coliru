#include <functional>
#include <tbb/concurrent_queue.h>
#include <thread>
#include <utility>

template<typename T>
class actor {
public:
    template<typename F>
    explicit actor(F callback)
        : queue{}, thread{[&, this] { callback(*this); }} { }
    
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
    tbb::concurrent_bounded_queue<T> queue;
    std::thread thread;
};

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <tuple>


auto logger_actor_ptr = new actor<std::string>{[] (actor<std::string>& self) {
    for (;;) {
        auto message = self.receive();
        std::cout << self.receive() << '\n';
    }
}};
auto& logger_actor = *logger_actor_ptr;

auto random_number_generator_actor_ptr = new actor<std::tuple<actor<int>*, int, int>> {[] (actor<std::tuple<actor<int>*, int, int>>& self) {
    std::mt19937 prng(std::time(nullptr));
    for (;;) {
        auto message = self.receive();
        std::uniform_int_distribution<> dis(std::get<1>(message), std::get<2>(message));
        std::get<0>(message)->send(dis(prng));
    }
}};

auto& random_number_generator_actor = * random_number_generator_actor_ptr;

auto main_actor_ptr = new actor<int>{[] (actor<int>& self) {
    for (int i = 0; i < 10; ++i) {
        random_number_generator_actor.send(std::make_tuple(&self, 0, 10));
        int x = self.receive();
        logger_actor.send(std::to_string(x));
    }
}};

auto& main_actor = *main_actor_ptr;



int main() {
    sleep(1);
}
