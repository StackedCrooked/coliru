#include <iostream>

struct loud {
    loud() {}
    loud(const loud&) {std::cout << "C";}
    loud(loud&&) {std::cout << "M";}
};

template<class T>
struct Node
{
    T value;
    Node(T &&value)
        : value(std::forward<T>(value)) { }
};


int main()
{
    loud l;

    //Node<loud> x0(l); // main.cpp:22:19: error: no matching function for call to ‘Node<loud>::Node(loud&)’
    std::cout << ".\n";
    Node<loud> x1(std::move(l));
    std::cout << ".\n";
    Node<loud&> x2(l);
    std::cout << ".\n";
    //Node<loud&> x3(std::move(l)); // error: no matching function for call to ‘Node<loud&>::Node(std::remove_reference<loud&>::type)’
    std::cout << ".\n";
}