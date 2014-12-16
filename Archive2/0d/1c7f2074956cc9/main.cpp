#include <iostream>
#include <string>
#include <vector>
#include <tuple>

struct Mediator {
    std::vector<struct Object*> objects;

    void registerObject (Object* o) {objects.emplace_back(o);}

    template <typename RET, typename... ARGS1, typename... ARGS2>
    RET change (Object*, RET (Object::*)(ARGS1...), ARGS2...);
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
    RET change (RET (Object::*f)(ARGS1...), ARGS2&&... args) {
        return mediator.change(this, f, std::forward<ARGS2>(args)...);
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

struct namedObjectChangeParameters {
    int value;
    double rating;
    char letter;
    long tag;
    
    explicit namedObjectChangeParameters(const Object& o) :
        value(o.value), rating(o.rating), letter(o.letter), tag(o.tag) {}
        
    void change(int a) {value=a;}
    void change(double b) {rating=b;}
    void change(char c) {letter=c;}
    void change(long d) {tag=d;}
    
    template<typename t0, typename... ARGS2>
    void change(t0 first, const ARGS2&...rest) {
        change(first);
        change(rest...);
    }
};

template <typename RET, typename... ARGS1, typename... ARGS2>
RET Mediator::change (Object* o, RET (Object::*f)(ARGS1...), const ARGS2&... args) {
    namedObjectChangeParameters t(*o);
    t.change(args...);
    for (Object* x : objects) {
        (x->*f)(t.value, t.rating, t.letter, t.tag);
    }
}


int main() {
    Mediator mediator;
    Object *a = new A(6, 1.2, 'a', 1111, mediator);
    Object *b = new B(2, 6.5, 'b', 2222, mediator);
    Object *c = new C(4, 0.8, 'c', 3333, mediator);

    c->change (&Object::adjust, 8, 'k');
}