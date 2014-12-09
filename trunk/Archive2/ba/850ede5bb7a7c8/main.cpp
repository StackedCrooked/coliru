#include <iostream>    

using namespace std;    

struct A
{
    int m_count;
    auto count() -> decltype(m_count) { return m_count; }
};
int main(){
    A a { 42 } ;
    std::cout << a.count();
    return 0;
}