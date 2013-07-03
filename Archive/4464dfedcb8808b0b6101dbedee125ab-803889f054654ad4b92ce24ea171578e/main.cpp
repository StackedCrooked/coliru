#include <iostream>

template<class T>
struct Node
{
    T value;
    Node(T &&value)
        : value(std::forward<T>(value)) { }
};


int main()
{
    std::string i = "HI";

    Node<std::string> x(i); // ok
    std::cout << i;
}