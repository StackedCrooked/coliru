#include <functional>
#include <iostream>


using namespace std::placeholders;


template<typename T>
struct ptr_or_val {
    ptr_or_val(T& data) : m_data(data) {}

    operator T&() { return m_data; }
    operator T*() { return &m_data; }

private:
    T& m_data;
};


template<typename func_type>
struct test {
    func_type m_func;

    test(func_type func) : m_func(func) {}

    void do_something(int i) {
        m_func(ptr_or_val<int>(i));
    }
};


template<typename func_type>
test<func_type> make_test(func_type func) {
    return {func};
}


void style_a(int id) {
    std::cout << "style_a(" << id << ")" << std::endl;
}

void style_b(int i, const int* id) {
    std::cout << "style_b(" << i << ", " << *id << ")" << std::endl;
}


int main() {
    auto ta = make_test(style_a);
    ta.do_something(1234);

    auto tb = make_test(std::bind(style_b, 69, _1));
    tb.do_something(1234);
}
