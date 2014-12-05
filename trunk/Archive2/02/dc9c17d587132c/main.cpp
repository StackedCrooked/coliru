#include <iostream>
#include <map>
 
struct A
{
    A(int) { };
    A(A&&) = delete;
};
 
int main()
{
    std::map<int, A> map;
    map.emplace(std::piecewise_construct,
                std::forward_as_tuple(1),
                std::forward_as_tuple(2));
}