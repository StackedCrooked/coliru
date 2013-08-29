#include <functional>
#include <iostream>


using namespace std::placeholders;


template<typename func_type>
struct test {
    func_type m_func;
    
    test(func_type func) : m_func(func) {}
    
    void do_something(int i) {
        m_func(i);
    }
};


template<typename func_type>
test<func_type> make_test(func_type func) {
    return {func};
}


void style_a(int id) {
    std::cout << "style_a(" << id << ")" << std::endl;
}

void style_b(int i, int* id) {
    std::cout << "style_a(" << i << ", " << *id << ")" << std::endl;
}


int main() {
    auto ta = make_test(style_a);
    ta.do_something(1234);
    
    int some_int = 69;
    auto tb = make_test(std::bind(style_b, _1, &some_int));
    tb.do_something(1234);
}