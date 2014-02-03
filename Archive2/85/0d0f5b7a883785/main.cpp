#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>

template<typename Event>
struct Function {
    typedef boost::function<void(Event)> type;
};

template<typename Event>
void subscribe(typename Function<Event>::type const&) {
    
}

struct Handler {
    void operator()(int) {
    }
};

void handler(int) {
}

struct Foo {
    void handler(int) {
    }
};

int main()
{
    subscribe<int>(Handler());
    subscribe<int>(handler);
    Foo foo;
    subscribe<int>(boost::bind(&Foo::handler, &foo, _1));
    return 0;
}
