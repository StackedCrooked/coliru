#include <iostream>
#include <map>
#include <string>
 
struct A
{
public:
    A(std::string s, int i) : _s{std::move(s)}, _i{i} { };
    A(A const&) = delete;
    A(A&&) = delete;   
    A& operator = (A const&) = delete;
    A& operator = (A&&) = delete;   
    ~A() = default;
    void print() { std::cout << _i; }
private:
    std::string _s;
    int _i;
};
 
int main()
{
    std::map<int, std::pair<int, A>> map;
    
    map.emplace(std::piecewise_construct,
                std::forward_as_tuple(42),
                std::forward_as_tuple(std::piecewise_construct, 
                                      std::forward_as_tuple(1337), 
                                      std::forward_as_tuple("Hello", 42)));
                
    map.at(42).second.print();
}