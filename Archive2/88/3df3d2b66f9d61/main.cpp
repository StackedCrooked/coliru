#include <iostream>

template<int* int_addr>
struct temp_on_int{
    temp_on_int() {}
    void print() {
        std::cout << *int_addr << std::endl;
    }
};


template<char* str_addr>
struct temp_on_string{
    temp_on_string() {}
    void print() {
        std::cout << str_addr << std::endl;
    }
};

static int i = 0;
static char j = 'h';
// static char* k = "hi";

int main() {

    temp_on_int<&i> five;
    i = 6;
    five.print();

    temp_on_string<&j> h;
    h.print();

    // temp_on_string<k> hi;
    // hi.print();
}