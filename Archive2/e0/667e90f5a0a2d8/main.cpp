#include <iostream>
#include <vector>
#include <algorithm>

struct C { int x, y; };

struct B {
    const C* c;
    B& operator=(const C& c) { this->c = &c; return *this; }    
};

struct A {
    std::vector<C> c_array;
    std::vector<B> b_array;
    A() {}
    A(const A& a) { *this = a; }
    A& operator=(const A& a) {
        c_array = a.c_array;
        b_array = a.b_array;
        // re-assign references only using `operator=(const C&)` :
        std::copy_n(c_array.begin(), c_array.size(), b_array.begin());
        return *this;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) { for (auto& el : vec) { os << el << ' '; } return os; }
std::ostream& operator<<(std::ostream& os, const C& c) { os << "[ C | " << c.x << "," << c.y << "]"; return os; }
std::ostream& operator<<(std::ostream& os, const B& b) { os << "[ B | " << b.c << ":" << *b.c << "]"; return os; }
std::ostream& operator<<(std::ostream& os, const A& a) { os << "[ A | " << a.c_array << "," << a.b_array << "]"; return os; }

int main() {
    
    // Init and print a1
    A a1; a1.c_array = { {1,2}, {3,4} }; a1.b_array = { B{ &a1.c_array[0] } , B{ &a1.c_array[1] } };
    std::cout << a1 << std::endl;
    
    // Init and print a2
    A a2 = a1;
    std::cout << a2 << std::endl;
    
    // Change a1, should be no effect on a2
    std::cout << "-----------" << std::endl;
    a1.c_array={ {5,6}, {7,8} };
    a1.b_array={ B{&a1.c_array[0]} ,B{&a1.c_array[1]} };
    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
}
