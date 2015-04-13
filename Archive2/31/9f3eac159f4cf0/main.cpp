#include <string>
#include <stdexcept>
#include <iostream>
struct Node
{
    Node* next;
    int data;
    // deep-copying copy constructor
    Node(const Node& other)
      : next(other.next ? new Node(*other.next) : NULL)
      , data(other.data)
    {}
    Node(int d) : next(NULL), data(d) {}
    ~Node() { delete next ; }
};
int main()
{   
    // simple rvalue example
    int n = 1>2 ? 10 : 11;  // 1>2 is false, so n = 11
    // simple lvalue example

    int m = 10; 
    (n == m ? n : m) = 7; // n == m is false, so m = 7
    std::cout << m << ' ' << n << '\n';
    // throw example
    std::string str = 2+2==4 ? "ok" : throw std::logic_error("2+2 != 4");
    std::cout << str;
}