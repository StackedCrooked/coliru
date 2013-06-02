#include <iostream>

template<typename T>
void showMessage(T &&t) {
    std::cout << t << "\n";
}

template<typename Head, typename... Tail> 
void showMessage(Head &&head, Tail&&... tail) {
    std::cout << head;
    showMessage(std::forward<Tail>(tail)...);
}

int main() {
    showMessage("value1: ", 5, " and value2: ", 'a');
}