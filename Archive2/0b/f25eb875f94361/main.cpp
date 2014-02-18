#include <functional>



template<size_t I, size_t N, typename T, class F, class R>
constexpr R reduce_impl(const std::array<T, N>&, F&&, R&& r, typename std::enable_if<(I==N),void>::type* =0) 
{return std::forward<R>(r);}

template<size_t I, typename T, std::size_t N, class F, class R>
constexpr auto reduce_impl(const std::array<T, N>& a, F&& f, R&& r, typename std::enable_if<(I<N),void>::type* =0)
-> decltype(reduce_impl<I+1>(a, std::forward<F>(f), f(std::forward<R>(r), a[I])))
{return reduce_impl<I+1>(a, std::forward<F>(f), f(std::forward<R>(r), a[I]));}

template<typename T, std::size_t N, class F>
constexpr auto reduce(const std::array<T, N>& a, F&& f)
-> decltype(reduce_impl<1>(a, std::forward<F>(f), a[0]))
{return reduce_impl<1>(a, std::forward<F>(f), a[0]);}



struct plus { //duplicate of C++0y std::plus<void>
    template<class T, class U>
    constexpr auto operator()(T&& t, U&& u) const
    ->decltype(std::forward<T>(t)+std::forward<U>(u))
    {return std::forward<T>(t)+std::forward<U>(u);}
};

template<int I>
struct wierd_adder {
    template<int J>
    constexpr wierd_adder<I+J> operator+(wierd_adder<J>) const
    {return {};}
    constexpr operator int() const {return I;}
};

#include <iostream>
#include <vector>

int main() {
    std::cout << reduce(std::array<int, 3>{{5,7,11}}, plus()) << '\n'; //3 integers
    std::cout << reduce(std::array<std::string, 2>{{"HELLO","WORLD"}}, plus()) << '\n'; //2 strings
    std::cout << reduce(std::array<std::vector<int>, 1>{{{3}}}, plus()).front() << '\n'; //1 object that doesn't even work
    std::cout << reduce(std::array<wierd_adder<1>, 2>{{{},{}}}, plus()) << '\n'; //objects that return completely unrelated types
}

    