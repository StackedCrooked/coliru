#include <iostream>
#include <type_traits>

struct animal { virtual ~animal() = 0; };
struct cat : animal { };
struct elephant : animal { };

animal::~animal() { } 

struct car { virtual ~car() = 0; };
struct trabant : car { };
struct lada : car { };

car::~car() { }

template <typename T>
typename std::enable_if<std::is_base_of<animal, T>::value>::type
foo(T&&) { }

template <typename T>
typename std::enable_if<std::is_base_of<car, T>::value>::type
bar(T&&) { }

template <typename T>
typename std::enable_if<std::is_base_of<animal, T>::value>::type
whatever(T&&) {
    std::cout << "Got an animal\n";
}

template <typename T>
typename std::enable_if<std::is_base_of<car, T>::value>::type
whatever(T&&) {
    std::cout << "This is a car\n";
}

int
main() {
    foo(cat{});
    foo(elephant{});
        
    bar(trabant{});
    bar(lada{});
    
    whatever(elephant{});
    whatever(trabant{});
}
