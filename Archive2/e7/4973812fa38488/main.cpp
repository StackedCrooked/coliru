#include <iostream>
#include <type_traits>

struct animal { virtual ~animal() = 0; };
struct cat : animal { };
struct elephant : animal { };

struct car { virtual ~car() = 0; };
struct trabant : car { };
struct lada : car { };

animal::~animal() { }
car::~car() { }

template <typename T>
typename std::enable_if<std::is_base_of<animal, T>::value>::type
foo(T) { }

template <typename T>
typename std::enable_if<std::is_base_of<car, T>::value>::type
bar(T) { }

int
main() {
    foo(cat{});
    foo(elephant{});
    foo(trabant{});
    
    bar(trabant{});
    bar(lada{});
    //bar(elephant{});
}
