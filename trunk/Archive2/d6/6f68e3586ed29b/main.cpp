#include <atomic>

template <class T>
void test() {
    typedef std::atomic<T> A;
    A a;
}

struct A {
    int i;
    explicit A(int d = 0) : i(d) {}
};

int main() {
    test<A>();
}