#include <iostream>
#include <queue>
#include <stdexcept>

bool error = false;
struct A {
    A(int i) : i(i) { }
    A(const A& a) : i(a.i) { if (error) throw std::runtime_error("copy"); }
    A(A&& a) : i(a.i) { if (error) throw std::runtime_error("move"); }
    int i;
};

template<class Q>
struct Popper {
    Popper(Q* q) : q(q) { }
    ~Popper() { if (q) q->pop(); error = true; }
    void abort() { q = nullptr; }
    Q* q;
};

template<class Q>
typename Q::value_type get_and_pop(Q& q) {
    Popper<Q> popper(&q);
    try { return std::move_if_noexcept(q.front()); }
    catch (...) { popper.abort(); throw; }
}

int main(int argc, char** argv) {
    std::queue<A> q;
    q.push(42);
    try {
        A a = get_and_pop(q);
        (void) a;
    } catch (const std::exception& e) {
        std::cout << e.what() << " exception\n";
    }
    std::cout << q.size() << "\n";
}