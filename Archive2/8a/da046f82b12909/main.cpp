#include <iostream>

#include <cstdlib>

template <typename T>
struct A
{
    A() : value_(T()) {}
    A(const T& value) : value_(value) {}
    ~A(){}

    const T& get() const { return value_; }
    void set(const T& value) { value_ = value; }
private:
    T value_;
};

int main(void) {
    typedef int T;

    A<T> a(68);
    const T& result = a.get();

    std::cout << result << std::endl;

    a.set(500);

    std::cout << result << std::endl;

    return EXIT_SUCCESS;    
}