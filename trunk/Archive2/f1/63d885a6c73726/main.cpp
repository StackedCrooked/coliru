#include <iostream>
#include <set>
#include <vector> 

template<typename T> 
auto foo(T t) -> decltype(t.push_back(1), void()) {
    std::cout << "push_back\n";
    t.push_back(1);
}

template<typename T>
auto foo(T t) -> decltype(t.insert(1), void()) {
    std::cout << "insert\n";
    t.insert(1);
}

int main() {
    std::vector<int> v;
    std::set<int> s;
    
    foo(v);
    foo(s);
}