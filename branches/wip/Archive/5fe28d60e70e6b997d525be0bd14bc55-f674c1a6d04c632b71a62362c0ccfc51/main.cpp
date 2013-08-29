#include <memory>
#include <vector>
#include <iostream>
#include <functional>

struct A {
    int a;
    A(int b): a(b) { std::cout << "A(int)\n"; }
    ~A() { std::cout << "~A()\n"; }
    A(const A& o): a(o.a) { std::cout << "A(A&)\n"; }
    A(A&& o): a(o.a) { std::cout << "A(A&&)\n"; }
    void print() { std::cout << "print(" << a << ")\n"; }
    void hello() { std::cout << "hello from " << a << '\n'; }
};

template<typename T>
struct Stuff {
private:
    std::vector<std::shared_ptr<T>> cache;
public:
    std::shared_ptr<T> get(unsigned index) {
        return std::shared_ptr<T>(cache[index]);
    }
    Stuff& insert(T* elem) {
        cache.push_back(std::shared_ptr<T>(elem));
        return *this;
    }
    template<typename... Args>
    Stuff& insert(Args&&... args) {
        cache.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
        return *this;
    }

    template<typename Callable>
    void apply(Callable&& func) {
        for(auto&& ptr : cache) {
            if(ptr)
                func(ptr);
        }
    }

    template<typename Callable, typename... Args>
    void apply(Callable&& func, Args&&... args) {
        int indices[sizeof...(args)] = { std::forward<Args>(args)... };
        for(auto&& index : indices) {
            if(cache[index])
                func(cache[index]);
        }
    }
};

struct Func {
    void operator()(std::shared_ptr<A> type) {
        type->print();
    }
};

int main() {
    Stuff<A> stuff;
    Func function;
    stuff.insert(100).insert(new A(200)).insert(300).insert(400);
    stuff.apply(function, 2, 1, 3);
    stuff.apply(std::bind(&A::hello, std::placeholders::_1));
}