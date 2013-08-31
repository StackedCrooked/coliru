#define TRACE std::cout << __FILE__ << ":" << __LINE__ << "(" << __PRETTY_FUNCTION__ << ")" << std::endl;

#include <functional>
#include <tbb/concurrent_queue.h>
#include <thread>
#include <utility>
#include <iostream>

template<typename T>
class actor {
public:
    template<typename F>
    explicit actor(F callback) :
        queue{}, thread{[=] {
            TRACE
            callback(*this);
            TRACE
        } }
    {
    }
    
    ~actor() {
            TRACE
        thread.join();
            TRACE
    }
    
    void send(T const& message) {
            TRACE
        queue.push(message);
            TRACE
    }
    
    T receive() {
            TRACE
        T message;
            TRACE
        queue.pop(message);
            TRACE
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

int main() {
    actor<int> main_actor{[] (decltype(main_actor)& self) {
        actor<std::string> logger_actor{[] (decltype(logger_actor)& self) {
            for (;;) {
            TRACE
                auto message = self.receive();
            TRACE
                std::cout << self.receive() << '\n';
            TRACE
            }
        }};
        
        actor<std::tuple<actor<int>*, int, int>> random_number_generator_actor{[] (decltype(random_number_generator_actor)& self) {
            std::mt19937 prng(std::time(nullptr));
            for (;;) {
            TRACE
                auto message = self.receive();
            TRACE
                std::uniform_int_distribution<> dis(std::get<1>(message), std::get<2>(message));
            TRACE
                std::get<0>(message)->send(dis(prng));
            TRACE
            }
        }};
    
        for (int i = 0; i < 10; ++i) {
            TRACE
            random_number_generator_actor.send(std::make_tuple(&self, 0, 10));
            TRACE
            int x = self.receive();
            TRACE
            logger_actor.send(std::to_string(x));
            TRACE
        }
    }};
}
