#include <iostream>
#include <vector>
#include <memory>

struct base {
    virtual void print() const = 0;
    virtual ~base() {}
};

template<typename T>
struct a : public base {
    T t;
    a() = default;
    a(T t): t(t) {}
    
    ~a() {
        std::cout << "Deleted!" << std::endl;
    }
    
    virtual void print() const {
        std::cout << t << '\n';
    }
    void set(T stuff) {
        t = stuff;
    }
};

void f(const base* b) {
    b->print();
}

template<typename T>
std::unique_ptr<a<T>> make(T arg) {
    return std::unique_ptr<a<T>>{ new a<T>(arg) };
}

int main() {
    std::vector<std::unique_ptr<base>> v;
    
    for(int i = 0; i < 6; ++i) {
        v.push_back(make<int>(i));
    }
    
    for(unsigned i = 1; i < 5; ++i) {
        v.push_back(make<float>(i * 2.4f));
    }

    for(const auto& e : v) {
        e->print();
    }
}