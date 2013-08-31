#include <iostream>

template<class T> using Alias = T;

 struct evaluate { 
     template<typename ...Ts> 
     constexpr evaluate(Ts&&...) {} 
};

template<class ...Ts>
void function(Ts... Vs) {    \
    evaluate{std::cout<<Vs...};
    ///Alias<char[]> { '\0', (void(std::cout << Vs), '\0')... };
}

int main() {
    function("APPLE ", 3);
}