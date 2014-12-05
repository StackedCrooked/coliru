#include <iostream>
#include <map>
 
struct A
{
public:
    A(int x) : _x{x} { };
    A(A const&) = delete;
    A(A&&) = delete;   
    A& operator = (A const&) = delete;
    A& operator = (A&&) = delete;   
    ~A() = default;
    void print() { std::cout << _x; }
private:
    int _x;
};
 
int main()
{
    std::map<int, A> map;
    
    map.emplace(std::piecewise_construct,
                std::forward_as_tuple(42),
                std::forward_as_tuple(1337));
                
    map.at(42).print();
}