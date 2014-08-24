#include <iostream>

struct base {
    virtual ~base() = default;
    virtual void print() const = 0;
};

struct derived : public base {
    virtual void print() const {
        std::cout << "hello world\n";
    }
};

struct test {
    void print() const {
        std::cout << "testing\n";
    }
};

struct stuff {
    void print() const {
        std::cout << "testing again\n";
    }
};


// polymorphism

void polymorphism(const base& b) {
    b.print();
}

// generic programming

template<typename T>
void generic(const T& t) {
    t.print();
}

int main() {
    polymorphism(derived{});
    std::cout << "----\n";
    generic(derived{});
    generic(test{});
    generic(stuff{});
}