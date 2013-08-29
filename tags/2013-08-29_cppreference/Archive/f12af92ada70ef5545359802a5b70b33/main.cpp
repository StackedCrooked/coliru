#include <cassert>
#include <cstddef>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <memory>
#include <mutex>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

template<typename T> struct Wrap;

template<typename T> struct DefaultWrapTraits {
    void before() { TRACE };
    void after()  { TRACE };

    const Wrap<T> & get_Wrap() const { return static_cast<Wrap<T>&>(*this); }
    Wrap<T> & get_Wrap() { return static_cast<Wrap<T>&>(*this); }

    const T & get_value() const { return *get_Wrap().t; }
    T & get_value() { return *get_Wrap().t; }
};

template<typename T> struct WrapTraits : DefaultWrapTraits<T> {};

template<typename T> struct Wrap : WrapTraits<T> {
    Wrap(const T & t) : t(const_cast<T*>(&t)) { this->before(); }
    ~Wrap() { this->after(); }

    const T * operator->() const { return t; }
    T * operator->() { return t; }

    Wrap(Wrap&&) = default;
    Wrap& operator=(Wrap&&) = default;

    Wrap(const Wrap&) = delete;
    Wrap& operator=(const Wrap&) = delete;

    T * t;
};

template<class T> struct Proxy {
    template<typename ...Args>
    explicit Proxy(Args && ...args): t(std::forward<Args>(args)...) { }

    Wrap<T> operator->() const {
        return Wrap<T>(t);
    }
    T t;
};

struct Item {
    void foo() const { TRACE }
    void bar() const { TRACE }
};

template<> struct WrapTraits<Item> : DefaultWrapTraits<Item> {
    void before() { std::cout << "SPECIAL BEFORE! (" << &get_value() << ")" << std::endl; }
};

template<> struct WrapTraits<std::string> : DefaultWrapTraits<std::string> {
    void before() { std::cout << "Before: " << get_value() << std::endl; }
    void after() { std::cout << "After: " << get_value() << std::endl; }
};

int main() {
    Proxy<Item> item;
    item->foo();

    std::cout << "\nWith std::string:" << std::endl;
    Proxy<std::string> s;

    std::cout << "\nPushing back a character: " << std::endl;
    s->push_back('a');

    std::cout << "\nClearing the string: " << std::endl;
    s->clear();
}
