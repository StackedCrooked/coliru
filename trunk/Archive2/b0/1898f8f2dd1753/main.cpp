#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

/*
// contained_type<C>::type is T when C is vector<T, ...>, set<T, ...>, or std::array<T, N>.
// Better to just use `typename C::value_type` instead, unless bad containers are involved
template <typename T, typename...>
struct contained_type { };

template <template <typename ... Cs> class C, typename T, typename... Ts>
struct contained_type<C<T, Ts...>> { using type = T; };

template <typename T, size_t N>
struct contained_type<std::array<T, N>> { using type = T; };
*/

// replace_type<K, T, U>::type is similar to K but with its parameters changed from T to U
// e.g. replace_type<std::set<int, std::less<int>, std::allocator<int>>, int, std::string>::type
//      is std::set<std::string, std::less<std::string>, std::allocator<std::string>>
template <typename K, typename ...>
struct replace_type { using type = K; };

template <typename K, typename U>
struct replace_type<K, K, U> { using type = U; };

template <template <typename... Ks> class K, typename T, typename U, typename... Ks>
struct replace_type<K<Ks...>, T, U> { using type = K<typename replace_type<Ks, T, U>::type ...>; };

template <typename T, size_t N, typename U>
struct replace_type<std::array<T, N>, T, U> { using type = std::array<U, N>; };

// map-like classes are harder. You have to replace both the key and the key-value pair types
// ...and prevent ambiguity on pair-pair conversions.
template <typename T1, typename T2, typename U1, typename U2>
struct replace_type<std::pair<T1, T2>, std::pair<T1, T2>, std::pair<U1, U2>>
{
    using type = std::pair<U1, U2>;
};

template <template <typename...> class K, typename T1, typename T2, typename U1, typename U2, typename... Ks>
struct replace_type<K<T1, T2, Ks...>, std::pair<const T1, T2>, std::pair<const U1, U2>>
{
    using type = K<U1, U2, 
        typename replace_type< 
            typename replace_type<Ks, T1, U1>::type,
            std::pair<const T1, T2>,
            std::pair<const U1, U2>
        >::type ...
    >;
};

//
// transform_container(const Container& c, Functor f)
// return a container similar to c, but storing value types determined by
// result of transformation functor f. Works cleanly for STL containers with insert,
// and almost works for std::array.
//
template <
    typename Container,
    typename Functor,
    typename T = typename Container::value_type,
    typename U = typename std::result_of<Functor(T)>::type,
    typename OutContainer = typename replace_type<Container, T, U>::type
>
OutContainer transform_container(const Container& c, Functor &&f)
{
    OutContainer ret;
    std::transform(std::begin(c), std::end(c), std::inserter(ret, std::end(ret)), f);
    return ret;
}

namespace std { // cheat so we can 'review' maps.
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::pair<const T1, T2>& p)
    {
        return os << "<" << p.first << ", " << p.second << ">", os;
    }
}

template <typename C1, typename T1 = typename C1::value_type, typename C2, typename T2 = typename C2::value_type>
void review(std::string name, const C1& c1, const C2& c2)
{
    std::cout << name << "(" << typeid(T1).name() << " -> " << typeid(T2).name() << "): ";
    std::copy(std::begin(c1), std::end(c1), std::ostream_iterator<T1>(std::cout, ", "));
    std::cout << "==> ";
    std::copy(std::begin(c2), std::end(c2), std::ostream_iterator<T2>(std::cout, ", "));
    std::cout << "\n";
}

int main()
{
    std::map<int, char> map{ {1, 'a'}, {2, 'b'}, {3, 'c'} };
    std::unordered_map<int, char> umap{ {1, 'a'}, {2, 'b'}, {3, 'c'} };
    std::set<int> set{ 1, 2, 3, 4, 5 };
    std::vector<int> vec{ 1, 2, 3, 4, 5 };
    std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
    
    auto x2 = [](int i) { return i * 2; };
    auto tos = [](int i) { return std::to_string(i); };
    auto rev = [](std::pair<int, char> p) -> std::pair<const char, int> { return std::make_pair(p.second, p.first); };
    auto dupkey = [](std::pair<int, char> p) -> std::pair<const int, int> { return std::make_pair(p.first, p.first); };
    auto dupval = [](std::pair<int, char> p) -> std::pair<const char, char> { return std::make_pair(p.second, p.second); };
    
    auto tset = transform_container(set, x2);
    review("tset", set, tset);

    auto tvec = transform_container(vec, x2);
    review("tvec", vec, tvec);

    auto sset = transform_container(set, tos);
    review("sset", set, sset);
    
    auto svec = transform_container(vec, tos);
    review("svec", vec, svec);
    
    auto swapmap = transform_container(map, rev);
    review("swapmap", map, swapmap);
    
    auto swapumap = transform_container(umap, rev);
    review("swapumap", umap, swapumap);
    
    auto dupkeymap = transform_container(map, dupkey);
    review("dupkeymap", map, dupkeymap);
    
    auto dupvalumap = transform_container(umap, dupval);
    review("dupvalmap", umap, dupvalumap);

    // uncomment following to see compilation errors on std::inserter(std::array<int, 5>)
    
    //auto tarr = transform_container(arr, x2);
    //review("tarr", arr, tarr);
    
    //auto sarr = transform_container(arr, tos);
    //review("sarr", arr, sarr);
    
    return 0;
}