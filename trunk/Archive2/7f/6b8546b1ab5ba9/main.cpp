#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

template <class>
struct Printer;

template <template<typename, typename> class C, template <typename> class A, typename T>
struct Printer< C<T, A<T>> > {
    void doSth() {
        std::cout << "sequence\n";
    }
};

template <template<typename, typename, typename, typename> class C, template <typename> class Comp, template <typename> class A, typename K, typename T>
struct Printer< C<K, T, Comp<K>, A<std::pair<const K,T>>> > {
    void doSth() {
        std::cout << "associative\n";
    }
};

template <template<typename, typename, typename, typename, typename> class C, template <typename> class Hash, template <typename> class Pred, template <typename> class A, typename K, typename T>
struct Printer< C< K, T, Hash<K>, Pred<K>, A<std::pair<const K,T>> > > {
    void doSth() {
        std::cout << "hashed\n";
    }
};


int main() {
    Printer<std::vector<int>> p0;
    Printer<std::list<int>> p1;
    Printer<std::map<int, float>> p2;
    Printer<std::unordered_map<int, float>> p3;
    p0.doSth();
    p1.doSth();
    p2.doSth();
    p3.doSth();
}
