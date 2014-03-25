#include <iostream>

template<unsigned int N>
struct A {
    void dostuff() const { std::cout << N << " "; }
};

template < int N > void run();

template <>        void run<-1>() {}
template < int N > void run() {
    run<N-1>();
    A<N>{}.dostuff();
}
 
int main() {
    run<10>();
}
