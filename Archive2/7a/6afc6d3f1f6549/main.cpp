#include <iostream>
#include <utility>
#include <functional>
#include <string.h>

namespace details {
    template<class F0, class F1>
    struct waterfall_call {
        typename std::decay<F0>::type f0;
        typename std::decay<F1>::type f1;
        template<class...Args>
        auto operator()(Args&&... args)const
        -> typename std::result_of<F0 const&(F1 const&,Args...)>::type
        {
            return f0( f1, std::forward<Args>(args)... );
        }
    };

    struct waterfall {
        template<class F0, class F1>
        waterfall_call<F0, F1> operator()( F0&& f0, F1&& f1 )const
        {
            return { std::forward<F0>(f0), std::forward<F1>(f1) };
        }

        template<class F0, class...Fs,
            class I=typename std::result_of<waterfall const&(Fs...)>::type
        >
        auto operator()( F0&& f0, Fs&&... fs )const
        -> typename std::result_of< waterfall( F0, I ) >::type
        {
            auto child = (*this)( std::forward<Fs>(fs)... );
            return (*this)( std::forward<F0>(f0), std::move(child) );
        }
        template<class F0>
        auto operator()(F0&&f0)const
        ->typename std::decay<F0>::type
        {
            return std::forward<F0>(f0);
        }
    };
}

template<class...Fs>
auto waterfall(Fs&&... fs )
-> typename std::result_of<details::waterfall(Fs...)>::type{
    return details::waterfall{}( std::forward<Fs>(fs)... );
}

struct a {
    template<class F>
    int operator()(F&& f, int x) const {
        std::cout << x << '\n';
        return f(1,2,x/2);
        return x;
    }
};

int b( std::function<double(double)> f, int x, int y, int z ) {
    std::cout << x << y << z << '\n';
    return 1./f(z + 3.14);
}

double c( std::function<int(char const*)> f, double d ) {
    std::cout << d << '\n';
    return 1./f( "hello" );
}

int d( char const* c ) {
    std::cout << c << '\n';
    return strlen(c);
}

int main() {
    int x = waterfall( a{}, b, c, d )(7);
    std::cout << x << '\n';
    int y = waterfall( a{}, b, c, d )(2);
    std::cout << y << '\n';
}