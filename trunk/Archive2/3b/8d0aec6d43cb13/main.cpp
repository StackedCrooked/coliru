#include <iostream>


enum Fruit {
    Apple,
    Orange
};

template <typename T>
void print_to_stream(std::ostream& o, const T& value) {
    o << value;
}

int main() {
    print_to_stream(std::cout, "hello\n");
    
    print_to_stream(std::cout, Orange);
 
    return 0;
}