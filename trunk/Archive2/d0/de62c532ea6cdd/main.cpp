#include <iostream>
#include <utility>
 
template<int N>
void print() {
    std::cout << "Number was " << N << std::endl;
}

template <int, int> struct printmany_helper;

template <int I, int Max>
struct printmany_helper {
    static void
    do_() {
        print<I>();
        printmany_helper<I + 1, Max>::do_();
    }
};

template <int Max>
struct printmany_helper<Max, Max> {
    static void
    do_() { }
};

template <int To>
void printmany() {
    printmany_helper<0, To>::do_();
}
 
int main() {
    printmany<10>();
}