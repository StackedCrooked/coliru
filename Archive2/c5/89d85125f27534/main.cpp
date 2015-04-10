#include <iostream>
#include <type_traits>

struct animal { };
struct cat : animal { };
struct elephant : animal { };

struct car { };
struct trabant : car { };
struct lada : car { };

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
    //foo(trabant{});
    
    bar(trabant{});
    bar(lada{});
    //bar(elephant{});
}
