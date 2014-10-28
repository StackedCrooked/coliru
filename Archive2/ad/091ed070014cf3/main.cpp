#include <mutex>
#include <iostream>

template<typename T>
void _DebugInner(T arg) {
    std::cout << arg << std::endl;
}

template<typename T, typename... Args>
void _DebugInner(T first, Args... rest) {
    std::cout << first << "    ";
    _DebugInner(std::forward<Args>(rest)...);
}

template<typename... Args>
void Debug(Args... args) {
    static std::mutex DebugMutex;

    std::lock_guard<std::mutex> lock(DebugMutex);

    _DebugInner(std::forward<Args>(args)...);
}

#include <thread>

int main() {
    bool moo = true;
    std::thread foo([&]() {
        while(moo) {
            Debug("foo");
        }
    });
    std::thread boo([&]() {
        while(moo) {
	        Debug("bar");
	    }
    });
    
    std::cin.get();
    moo = false;
    
    foo.join();
    boo.join();
    
    return 0;
}
