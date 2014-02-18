#include <iostream>
#include <string>
#include <vector>
#include <cstdio>


template <class T> std::ostream& operator<<(std::ostream& os, T t) {    std::printf("os, T\n");
return os;} 
namespace d {
    struct mystruct {operator int() {return 42;}}; 
    template <class T> T& operator<<(T& os, mystruct t) {std::printf("T, os\n"); return os << t;}
} 
struct mystruct_wrapper {
    mystruct_wrapper(d::mystruct& dd) : d_(dd) {} 
    d::mystruct& d_; 
    operator d::mystruct() {return d_;}
}; 
std::ostream& operator<<(std::ostream& os, d::mystruct t) {    std::printf("os, d::m\n"); return os; }
int main() 
{
    d::mystruct m; 
    mystruct_wrapper mw(m); 
    std::cout << m << std::endl;
}
