#include <iostream>
#include <string>
#include <type_traits>

enum MyEndl { my_endl };

class Logger {

public:

    void log(MyEndl x) { std::cout << std::endl; }

    template<typename T>
    void log(T val);

    template <typename T, typename ...Args>
    void log(T val, Args... args);
};

template<typename T>
void Logger::log(T val) {
    std::cout << val;
}

template<typename T, typename ...Args>
void Logger::log(T val, Args... args) {

    log(val);
    log(args...);

}

int main(int argc, char* argv[])
{
    Logger log;

    log.log("Nazdar ", "bazar ", 0, " cau", my_endl, "kik\n"); 

    std::cin.get();

    return 0;
}
