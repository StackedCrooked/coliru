#include <stdexcept>
#include <unistd.h>

enum result { ok, error };


template<typename F>
struct checked_function {
    checked_function(const F & f) : f(f) {}
    
    template<typename ...Args>
    void operator()(Args && ...args) const {
        if (f(std::forward<Args>(args)...) != ok) {
            throw std::runtime_error("fail");
        }
    }    
    
    F f;
};

template<typename F>
checked_function<F> make_checked(const F & f) {
    return checked_function<F>(f);
}



int foo() { return int(time(0)) % 2; }
int bar() { return int(time(0)) % 2; }

auto checked_foo = make_checked(&foo);
auto checked_bar = make_checked(&bar);


int main()
{
}