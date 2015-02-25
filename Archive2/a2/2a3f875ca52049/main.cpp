
#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

struct Fun {
    virtual void call(long val) = 0;
    virtual ~Fun() {}
};

struct Counter : Fun {
    long acc = 0;
    virtual void call(long x) {
        acc += x;
    }
};

std::vector<long> generate_vector() {
    const size_t S = 1000;
    std::vector<long> v;
    v.resize(S+1);
    v.at(S) = 1;
    return v;
}

struct Foo {
    std::vector<long> values = generate_vector();

    void vtable_for_each(Fun& fn) {
        for(auto x: values) {
            fn.call(x);
        }
    }

    template<class Fn>
    void template_for_each(Fn& fn) {
        for(auto x: values) {
            fn(x);
        }
    }
};

int main()
{
    Foo foo;
    boost::timer tm;
    {
        long acc = 0;
        auto fn = [&acc](long x) { acc += x; };
        foo.template_for_each(fn);

        tm.restart();
        acc = 0;
        for (int i = 0; i < 100000; i++) {
            foo.template_for_each(fn);
        }
        double t = tm.elapsed();
        std::cout << "Templated count - " << t << "s, val - " << acc << std::endl;
    }

    {
        Counter cnt;
        tm.restart();
        for (int i = 0; i < 100000; i++) {
            foo.vtable_for_each(cnt);
        }
        double t = tm.elapsed();
        std::cout << "Virtual count - " << t << "s, val - " << cnt.acc << std::endl;
    }
    return 0;
}