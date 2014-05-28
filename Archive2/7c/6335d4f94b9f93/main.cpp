#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <atomic>

namespace Engine {
    template<class return_type,class...arguments>
    class Timer{
        typedef std::function<return_type(arguments...)> _function_t;

    public:
        Timer(size_t interval,bool autoRun,_function_t function,arguments...args){
            _function = function;
            _interval = interval;
            if (autoRun) {
                Enable(args...);
            }
        }
        ~Timer(){
            if (Running()) {
                Disable();
            }
        }
        void Enable(arguments...args){
            if (!Running()) {
                _running=true;
                enable(_interval, _function, args...);
            }
        }
        void Disable(){
            if (Running()) {
                _running=false;
            }
        }
        std::atomic_bool const& Running()const{
            return _running;
        }
    protected:
        void enable(size_t interval,_function_t func,arguments...args){
            _thread =std::thread([&,func,interval,args...](){
                std::chrono::duration<long long,std::nano> inter(interval);
                auto __interval = std::chrono::microseconds(interval);
                auto deadline = std::chrono::steady_clock::now();
                while (_running) {
                    func(args...);
                    std::this_thread::sleep_until(deadline+=__interval);
                }
            });
            _thread.detach();
        }
    protected:
        _function_t _function;
        std::atomic_bool _running;
        size_t _interval;
        std::thread _thread;

    };

};

struct A {
    void foo() {std::cout << "HI";}
};

int main() {
    A obj;
    Engine::Timer<void,A*>::Timer(10000000, true, &A::foo, &obj);
    std::this_thread::sleep_for(std::chrono::seconds(2));
}