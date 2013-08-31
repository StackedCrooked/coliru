#include <iostream>

template<typename T>
class ptr {
private:
    T* value;
public:
    ptr(): value(nullptr) {}
    ptr(T* val): value(val) {}
    ptr(T val): value(&val) {}
    ~ptr() { delete value; }
    T& operator*() { return *value; }
    const T& operator*() const { return *value; }
    T* operator->() { return value; }
    const T* operator->() const { return value; }
    operator bool() const { return value != nullptr; }
};

class A {
public:
    int a;
    void print() { std::cout << a; }
};
int main() {
    ptr<A> p(new A);
    if(p) {
        p->a = 10;
        p->print();
    }
}
