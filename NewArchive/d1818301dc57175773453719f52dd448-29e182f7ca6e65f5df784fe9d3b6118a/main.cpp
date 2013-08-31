#include <iostream>

template<typename T>
void log(T &&t) {
    std::cout << t;    
}

template<typename Head, typename... Tail>
void log(Head &&head, Tail&&... tail) {
    std::cout << head;
    log(std::forward<Tail&&>(tail)...);
}

int main() {
    log("hi ", 3, ' ', 2 * 8);
}