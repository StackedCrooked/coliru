#include <iostream>
#include <utility>
#include <functional>

enum class Error {
    no_error,
    error
};
bool is_error(Error err){return err!=Error::no_error;}


template<class E, class C, class F>
auto waterfall_error( E&& e, C&& c, F&& f ) {
    return [c=(C)c,f=(F)f,e=(E)e](Error err, auto&&...args) {
        if (is_error(err)) e(err);
        else f( c, decltype(args)(args)... );
    };
}

template<class E, class C, class F0, class...Fs>
auto waterfall_error( E&& e, C&& c, F0&& f0, Fs&&... fs ) {
    auto child = waterfall_error( e, c, std::forward<Fs>(fs)... );
    return waterfall_error( e, std::move(child), std::forward<F0>(f0) );
}

template<class C, class...Fs>
auto waterfall( C&& c, Fs&&... fs ) {
    auto helper = waterfall_error( std::forward<C>(c), [](auto&&...){}, std::forward<Fs>(fs)... );
    return [helper = std::move(helper)](auto&&... args) {
        return helper( Error::no_error, decltype(args)(args)... );
    };
}

struct a {
    template<class F>
    void operator()(F&& f, int x) const {
        std::cout << x << '\n';
        f(Error::no_error, 1,2,x/2);
    }
};

void b( std::function<void(Error, double)> f, int x, int y, int z ) {
    std::cout << x << y << z << '\n';
    f(Error::no_error, z + 3.14);
}

void c( std::function<void(Error, char const*)> f, double d ) {
    std::cout << d << '\n';
    f( d > 6.?Error::no_error:Error::error, "hello" );
}

void d( std::function<void(Error)> f, char const* c ) {
    std::cout << c << '\n';
    f( Error::no_error );
}

int main() {
    Error err = Error::no_error;
    
    waterfall( [&](Error e){err=e;}, a{}, b, c, d )(7);
    switch(err) {
        case Error::no_error: std::cout << "no error\n"; break;
        case Error::error: std::cout << "error\n"; break;
    }
    waterfall( [&](Error e){err=e;}, a{}, b, c, d )(2);
    switch(err) {
        case Error::no_error: std::cout << "no error\n"; break;
        case Error::error: std::cout << "error\n"; break;
    }
}