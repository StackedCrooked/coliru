#include <iostream>
#include <queue>

bool print = false;
struct A {
    A(int i) : i(i) { }
    A(const A& a) noexcept : i(a.i) { if (print) std::cout << "copied " << i << "\n"; }
    A(A&& a) noexcept : i(a.i) { if (print) std::cout << "moved " << i << "\n"; a.i = 0; }
    int i;
};

template<class Q>
struct Popper {
    Popper(Q* q) : q(q) { }
    ~Popper() { if (q) q->pop(); if (print) std::cout << "unwound\n"; }
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
    print = true;
    A a = get_and_pop(q);
    std::cout << a.i << "\n";
}