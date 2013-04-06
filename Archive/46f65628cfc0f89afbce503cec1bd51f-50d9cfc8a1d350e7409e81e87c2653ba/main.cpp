#include <tuple>

template<typename TL, class T1, class T2> struct Functor{};
template< typename TL,
          template<size_t...> class T1, size_t... A1, // read only arguments
          template<size_t...> class T2, size_t... A2  // read-write arguments
        >
struct Functor< TL, T1<A1...>, T2<A2...>> {
    typedef void (*Type)(const typename std::tuple_element<A1, TL>::type* ... ,
                               typename std::tuple_element<A2, TL>::type* ...);

    Functor(Type) {}
};

void foo(const float  *,
         const int    *,
               double *)
{}

template<size_t ... T> struct Pack {};

int main()
{
    using Pixel = std::tuple<float, double, int>;
    Functor<Pixel, Pack<0,2>, Pack<1>> apply_foo(foo);
}