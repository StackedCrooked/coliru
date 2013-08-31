#include <iostream>

#define LOG_TEST(...) log(__FILE__, ':', __LINE__, ' ', __func__, ' ', __VA_ARGS__)

template<typename T>
void log(T &&t) {
    std::cout << t << '\n';    
}

template<typename Head, typename... Tail>
void log(Head &&head, Tail&&... tail) {
    std::cout << head;
    log(std::forward<Tail&&>(tail)...);
}

int main() {
    LOG_TEST("hi ", 3, ' ', 2 * 8);
    LOG_TEST("second line of output");
}