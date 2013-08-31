#include <iostream>

template<class T> using Alias = T;

template<class ...Ts>
void ignored(Ts&&... Vs) {
    Alias<char[]> { '\0', (void(Vs), '\0')... };
}

template<class ...Ts>
void function(Ts... Vs) {    \
    ignored(std::cout<<Vs...);
    ///Alias<char[]> { '\0', (void(std::cout << Vs), '\0')... };
}

int main() {
    function("APPLE ", 3);
}