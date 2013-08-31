#include <tuple>

template <class, unsigned int, template <class...> class, class>
struct repeat_helper;

template <class T, template <class...> class M, class... Args>
struct repeat_helper<T, 0, M, M<Args...>>
{
    typedef M<Args...> type;
};

template <class T, unsigned int n, template <class...> class M, class... Args>
struct repeat_helper<T, n, M, M<Args...>>
{
    typedef typename repeat_helper<T, n-1, M, M<Args..., T>>::type type;
};

template <class T, unsigned int n, template <class...> class M = std::tuple>
struct repeat
{
    using type = typename repeat_helper<T, n, M, M<>>::type;
};

int main( int argc, char** argv )
{
    repeat<double, 5>::type x = std::make_tuple( 1., 2., 3., 4., 5. );
    return 0;
}
