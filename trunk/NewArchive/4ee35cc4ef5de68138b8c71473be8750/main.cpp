#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>

class Stopwatch {
public:
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start;
    Stopwatch(): start(Clock::now()) {}
    void elapsed() {
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms\n";
    }
    void reset() {
        start = Clock::now();
    }
};

void printformat(const char* str) {
    while(*str) {
        if(*str == '%' && *(++str) != '%')
            throw std::runtime_error("Missing arguments");
        std::cout << *str++;
    }
}

template<typename T, typename... Args>
void printformat(const char* str, T value, Args... args) {
    while(*str) {
        if(*str == '%' && *(++str) != '%') {
            std::cout << value;
            printformat(str,args...);
            return;
        }
        std::cout << *str++;
    }
    throw std::logic_error("Too many arguments");
}

int main() {
    Stopwatch k;
    std::string str1 = "Hello";
    std::string str2 = "World";
    int i = 12345;
    int z = 4812;
    int w = i - z;
    printformat("% %!\n% - % = %\n",str1,str2,i,z,w);
    k.elapsed();
}