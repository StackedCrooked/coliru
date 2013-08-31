#include <iostream>
#include <vector>
#include <initializer_list>


struct test {
    int n;
    
    test() : n(0) { std::cout << "default construct " << std::endl; };
    test(int x) : n(x) { std::cout << "construct " << n << std::endl; };
    test(const test& rhs) : n(rhs.n) { std::cout << "copy construct " << n <<  std::endl; }
    test(test&& rhs) : n(rhs.n) { std::cout << "move construct " << n << std::endl; }
    
    test& operator=(const test&) { std::cout << "copy assign " << n << std::endl; return *this; }
    test& operator=(test&&) { std::cout << "move assign " << n << std::endl; return *this; } 
};


template<typename T>
struct some_container {
    std::vector<T> vec;
    
    some_container(std::initializer_list<T> list) {
        std::cout << "In some_container constructor: " << std::endl;
        vec.reserve(list.size());
        
        for(auto& e : list) {
            vec.push_back(e);
        }
    }
};



int main() {
    test t1(1);
    test t2(2);
    
    some_container<test> c = {
        t1,
        std::move(t2),
        test(3)
    };
}