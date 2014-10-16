#include <type_traits>
#include <algorithm>

struct F
{
    int operator()(bool a) & { return 1; }
};

template<
  typename T, typename A,
  typename Selector,
  typename R=typename std::result_of<Selector(T)>::type
>
    std::vector<R> select(std::vector<T, A> const & c, Selector&& s) {
    std::vector<R> v;
    std::transform(begin(c), end(c), back_inserter(v), std::forward<Selector>(s));
    return v;
}

int main()
{    
    std::vector<bool> a;
    select(a, F{});
}
