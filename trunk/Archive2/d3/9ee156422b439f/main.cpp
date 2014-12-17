#include <iostream>
#include <string>
#include <vector>
#include <tuple>

struct Mediator {
    std::vector<struct Object*> objects;

    void registerObject (Object* o) {objects.emplace_back(o);}

    template <typename RET, typename... ARGS1, typename... ARGS2>
    void change (Object*, RET (Object::*)(ARGS1...), const ARGS2&...);
};

struct Object {
    int value;
    double rating;
    char letter;
    long tag;
    Mediator& mediator;

    Object (int v, double r, char l, long s, Mediator& m) :
        value(v), rating(r), letter(l), tag(s), mediator(m) {mediator.registerObject(this);}

    virtual void adjust (int, double, char, long) = 0;

    template <typename RET, typename... ARGS1, typename... ARGS2>
    void change (RET (Object::*f)(ARGS1...), const ARGS2&... args) {
        return mediator.change(this, f, args...);
    }
};

struct A : Object {
    using Object::Object;
    virtual void adjust (int a, double b, char c, long s) override {
        std::cout << "Type A adjusted using values " << a << ", " << b << ", " << c << ", and " << s << "." << std::endl;
    }
};

struct B : Object {
    using Object::Object;
    virtual void adjust (int a, double b, char c, long s) override {
        std::cout << "Type B adjusted using values " << a << ", " << b << ", " << c << ", and " << s << "." << std::endl;
    }
};

struct C : Object {
    using Object::Object;
    virtual void adjust (int a, double b, char c, long s) override {
        std::cout << "Type C adjusted using values " << a << ", " << b << ", " << c << ", and " << s << "." << std::endl;
    }
};

template<class T> struct typetag {};

const int& get_type_from_class(const Object* o, typetag<int>) {return o->value;}
const double& get_type_from_class(const Object* o, typetag<double>) {return o->rating;}
const char& get_type_from_class(const Object* o, typetag<char>) {return o->letter;}
const long& get_type_from_class(const Object* o, typetag<long>) {return o->tag;}

template<class T> const T& get_T_by_type(const T& def) {return def;}
template<class T, class p0, class...pRest> const T& get_T_by_type(const T& def, const p0& discard, const pRest&...rest) {return get_T_by_type(def, rest...);}
template<class T, class...pRest> const T& get_T_by_type(const T& def, const T& returnme, const pRest&...rest) {return returnme;}

template <typename RET, typename... ARGS1, typename... ARGS2>
void Mediator::change (Object* o, RET (Object::*f)(ARGS1...), const ARGS2&... args) {
    for (Object* x : objects) {
        (x->*f)(
            get_T_by_type(get_type_from_class(o, typetag<ARGS1>{}),args...)
            ...
            );
    }
}


int main() {
    Mediator mediator;
    Object *a = new A(6, 1.2, 'a', 1111, mediator);
    (void)a;
    Object *b = new B(2, 6.5, 'b', 2222, mediator);
    (void)b;
    Object *c = new C(4, 0.8, 'c', 3333, mediator);

    c->change (&Object::adjust, 8, 'k');
}