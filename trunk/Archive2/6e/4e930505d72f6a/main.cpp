#include <utility>

template<class F, class G>
struct chained_t
{
    F f; G g;
    
    template<class... Ts>
    decltype(auto) operator()(Ts&&... ts)
    {
        return g(f(std::forward<Ts>(ts)...));
    }
};

//namespace detail
//{
template<class F, class G>
chained_t<F, G> operator->*(F f, G g){ return {f, g}; }
//} // detail::

//template<class... Fs>
//auto chain(Fs... fs){ return (fs ->* ...); }

#include <iostream>

int main()
{
    auto gen = []{ return 42; };
    auto trans = [](int i){ return i * 10; };
    auto out = [](int i){ std::cout << i; };
    //chain(gen, trans, out)();
    (gen ->* trans ->* out)();
}
