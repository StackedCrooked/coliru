#include <string>
#include <iostream>
#include <typeinfo>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;
using boost::dynamic_pointer_cast;

template<typename X, typename T>
shared_ptr<X> dynamic_clone(const shared_ptr<X>& x) {

    auto x_ = dynamic_pointer_cast<T>(x);
    return dynamic_pointer_cast<X>(x_ ? make_shared<T>(*x_) : x_);
}

template<typename X, typename T, typename N, typename... R>
shared_ptr<X> dynamic_clone(const shared_ptr<X>& x) {

    shared_ptr<T> nil_;

    auto t_ = dynamic_clone<X, T>(x);

    auto result_ = !t_ ? dynamic_clone<X, N, R...>(x) : t_;

    //if (nullptr == result_)
    //    throw std::bad_cast("incompatible dynamic clone");

    return result_;
}

struct Base {
    Base() {}
    Base(const Base&) {}
    virtual ~Base() {}
};

struct A : Base {
    A() : Base() {}
    A(const A& a) : Base(a) {}
    virtual ~A() {}
};

struct B : Base {
    B() : Base() {}
    B(const B& b) : Base(b) {}
    virtual ~B() {}
};

typedef shared_ptr<Base> Base_ptr;
typedef shared_ptr<A> A_ptr;
typedef shared_ptr<B> B_ptr;

template<typename T>
void show(const std::string& name, const shared_ptr<T>& x) {

    using std::cout;
    using std::endl;

    cout << name << " is " << (x ? "" : "not ") << "set" << endl;
}

int main() {

    auto base_ = dynamic_pointer_cast<Base>(make_shared<A>());

    show("base", base_);

    auto cloned_ = dynamic_clone<Base, B, A>(base_);

    show("cloned", cloned_);

    auto again_ = dynamic_clone<Base, B>(base_);

    show("again", again_);
}
