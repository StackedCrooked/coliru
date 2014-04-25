#include <utility>
#include <iostream>

template<class T>
void do_something(T const& t, int& i)
{
    std::cout << t << ' ' << i << '\n';
    ++i;
}

template<class F>
struct X
{
    F& foo;
    
    void operator()() {}
    
    template<class V, class... Args>
    void operator()(V&& v, Args&&... args)
    {
        foo( *this, std::forward<V>(v), std::forward<Args>(args)... );
    }
};

template<class F>
auto make_X(F& f)
{ return X<F>{f}; }

int main() {
    int i = 42;
    
    auto foo =
        [&] (auto f, auto && v, auto && ... args) {
            do_something(v, i);
            f(std::forward<decltype(args)>(args)...);
        };
    
    foo(make_X(foo), 1, 2, 3, 4);
}