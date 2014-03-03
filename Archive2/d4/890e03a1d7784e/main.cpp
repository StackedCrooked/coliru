#include <cassert>
#include <iostream>
#include <stdexcept> 
#include <type_traits> 

struct foo {       
    virtual ~foo() = default;
    
    template<typename T, typename = typename std::enable_if<std::is_same<T, int>::value>::type, typename = void>
    T fun();
    
    template<typename T, typename = typename std::enable_if<std::is_same<T, float>::value>::type>
    T fun();
};

struct bar_class1 : foo {
    int fun() {
        return 2;
    }
};

struct bar_class2 : foo {
    float fun() {
        return 3.5f;
    }
};

template<typename T, typename, typename Dummy>
T foo::fun() {
    if (auto *p = dynamic_cast<bar_class1 *>(this)) {
        return p->fun();
    } else if (dynamic_cast<bar_class2 *>(this)) {
        throw std::invalid_argument("Mismatching dynamic type.");
    } else {
        return 1;
    }
}

template<typename T, typename>
T foo::fun() {
    auto *p = dynamic_cast<bar_class2 *>(this);
    
    if (dynamic_cast<bar_class1 *>(this) || !p) {
        throw std::invalid_argument("Mismatching dynamic type.");
    } else if (auto *p = dynamic_cast<bar_class2 *>(this)) {
        return p->fun();
    }
    
    assert(false); //should never get here, but compiler doesn't know that
}

int main() {
    bar_class1 d1;
    bar_class2 d2;
    foo b;
    
    foo *pb = &b;
    foo *pd1 = &d1;
    foo *pd2 = &d2;
    
    std::cout << pb->fun<int>() << '\n';
    std::cout << pd1->fun<int>() << '\n';
    std::cout << pd2->fun<float>() << '\n';
    
    try {
        std::cout << pd2->fun<int>() << '\n';
    } catch (std::exception &ex) {
        std::cout << ex.what() << '\n';
    }
}