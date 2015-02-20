#include <thread>
#include <iostream>
#include <future>
 
int main()
{
    std::promise<int> result;
 
    std::thread t([&]{
            try {
                // code that may throw
                throw std::runtime_error("Example");
            } catch(...) {
                try {
                    // store anything thrown in the promise
                    result.set_exception(std::current_exception());
                } catch(...) {} // set_exception() may throw too
            }
    });
 
    try {
        std::cout << result.get_future().get();
    } catch(const std::exception& e) {
        std::cout << "Exception from the thread: " << e.what() << '\n';
    }
    t.join();
}