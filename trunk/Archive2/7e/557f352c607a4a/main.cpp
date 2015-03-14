#include <queue>
#include <iostream>

template<class Q>
struct Popper {
    Popper(Q& q) : q(q) { }
    ~Popper() { q.pop(); }
    Q& q;
};

template<class Q>
typename Q::value_type get_and_pop(Q& q) {
    Popper<Q> popper(q);
    return std::move(q.front());
}

int main(int argc, char** argv) {
    std::queue<int> q;
    q.push(42);
    q.push(43);
    std::cout << get_and_pop(q) << "\n";
    std::cout << q.size() << "\n";
}
