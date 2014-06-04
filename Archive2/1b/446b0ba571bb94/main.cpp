#include <iostream>

template <typename T>
struct cons { using type = T; };

template <typename... T>
struct Set {};

template <typename F, typename E>
struct Forwarder {
    Forwarder(F f): inner(f) {}
    
    template <typename... Args>
    void operator()(Args... args) { inner(cons<E>{}, args...); }
    
    F inner;
}; // struct Forwarder


template <typename FirstSet, typename... Sets, typename F>
void combine(F func);

template <typename Head, typename... Tail, typename... Sets, typename F>
void apply_set(F func, Set<Head, Tail...>, Sets... others);

template <typename Head, typename... Tail, typename... Sets, typename F>
void apply_set(F func, Set<>, Sets... others);

template <typename E, typename NextSet, typename... Sets, typename F>
void apply_item(F func, cons<E>, NextSet, Sets...);

template <typename E, typename F>
void apply_item(F func, cons<E> e);


template <typename Head, typename... Tail, typename... Sets, typename F>
void apply_set(F func, Set<Head, Tail...>, Sets... others) {
    apply_item(func, cons<Head>{}, others...);

    apply_set(func, Set<Tail...>{}, others...);
} // apply_set

template <typename... Sets, typename F>
void apply_set(F, Set<>, Sets...) {}

template <typename E, typename NextSet, typename... Sets, typename F>
void apply_item(F func, cons<E>, NextSet ns, Sets... tail) {
    Forwarder<F, E> forwarder(func);
    
    apply_set(forwarder, ns, tail...);
}

template <typename E, typename F>
void apply_item(F func, cons<E> e) {
    func(e);
} // apply_item


template <typename FirstSet, typename... Sets, typename F>
void combine(F func) {
    apply_set(func, FirstSet{}, Sets{}...);
} // apply_set

//
// Example
//
struct Dummy0 {}; struct Dummy1 {}; struct Dummy2 {};
struct Hello0 {}; struct Hello1 {};

struct Tested {
    Tested(int i): value(i) {}
    
    void operator()(cons<Dummy0>, cons<Hello0>) { std::cout << "Hello0 Dummy0!\n"; }
    void operator()(cons<Dummy0>, cons<Hello1>) { std::cout << "Hello1 Dummy0!\n"; }
    void operator()(cons<Dummy1>, cons<Hello0>) { std::cout << "Hello0 Dummy1!\n"; }
    void operator()(cons<Dummy1>, cons<Hello1>) { std::cout << "Hello1 Dummy1!\n"; }
    void operator()(cons<Dummy2>, cons<Hello0>) { std::cout << "Hello0 Dummy2!\n"; }
    void operator()(cons<Dummy2>, cons<Hello1>) { std::cout << "Hello1 Dummy2!\n"; }
    
    int value;
};

int main() {
    Tested tested(42);
    combine<Set<Dummy0, Dummy1, Dummy2>, Set<Hello0, Hello1>>(tested);
}