#include<functional>

template <class F> struct callable : F
{
    using F::operator();
};

template <class... Fs> struct make_overload_set : callable<Fs>...
{
    template <class... Ts> auto call(Ts &&... ts)
    {
        return this->operator()(std::forward<Ts>(ts)...);
    }
};

int main() {
return 0;
}