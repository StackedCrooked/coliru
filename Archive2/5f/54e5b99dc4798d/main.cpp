#include <type_traits>

template<typename T, std::size_t Position1, std::size_t Position2, bool AtPos1, bool AtPos2, typename Left, typename Middle, typename Right> struct SwapImpl;

template<typename T, std::size_t Position1, std::size_t Position2, template <T...> class Container, T...LeftAll, T LeftItem, T...Middle, T RightItem, T...RightAll> 
struct SwapImpl<T,Position1,Position2,false,false,Container<LeftAll...>,Container<LeftItem,Middle...,RightItem>,Container<RightAll...>> {
    using type = typename SwapImpl<T,Position1,Position2,sizeof...(LeftAll)+1==Position1,sizeof...(LeftAll)+sizeof...(RightAll)+1==Position2,Container<LeftAll...,LeftItem>,Container<Middle...>,Container<RightItem,RightAll...>>::type;    
};
template<typename T, std::size_t Position1, std::size_t Position2, template <T...> class Container, T...LeftAll, T LeftItem, T...Middle, T RightItem, T...RightAll> 
struct SwapImpl<T,Position1,Position2,true,false,Container<LeftAll...>,Container<LeftItem,Middle...,RightItem>,Container<RightAll...>> {
    using type = typename SwapImpl<T,Position1,Position2,true,sizeof...(LeftAll)+sizeof...(RightAll)+1==Position2,Container<LeftAll...>,Container<LeftItem,Middle...>,Container<RightItem,RightAll...>>::type;    
};
template<typename T, std::size_t Position1, std::size_t Position2, template <T...> class Container, T...LeftAll, T LeftItem, T...Middle, T RightItem, T...RightAll> 
struct SwapImpl<T,Position1,Position2,false,true,Container<LeftAll...>,Container<LeftItem,Middle...,RightItem>,Container<RightAll...>> {
    using type = typename SwapImpl<T,Position1,Position2,sizeof...(LeftAll)+1==Position1,true,Container<LeftAll...,LeftItem>,Container<Middle...,RightItem>,Container<RightItem,RightAll...>>::type;    
};
template<typename T, std::size_t Position1, std::size_t Position2, template <T...> class Container, T...LeftAll, T LeftItem, T...Middle, T RightItem, T...RightAll> 
struct SwapImpl<T,Position1,Position2,true,true,Container<LeftAll...>,Container<LeftItem,Middle...,RightItem>,Container<RightAll...>> {
    using type = Container<LeftAll...,RightItem,Middle...,LeftItem,RightAll...>;
};

// Swapping two elements of specified positions in a pack.
template <typename, std::size_t, std::size_t, typename> struct Swap;

template <typename T, std::size_t Position1, std::size_t Position2, template <T...> class Container, T... Ts>
struct Swap<T, Position1, Position2, Container<Ts...>> {
    using type = typename SwapImpl<T,Position1,Position2,Position1==0,Position2==sizeof...(Ts)-1,Container<>,Container<Ts...>,Container<>>::type;
};



#include <iostream>
template<int...Ts>
struct Container {
    static void p() {int c[] = {(std::cout<<Ts,0)...,0};}
};

int main() {
    Container<0,1>::p();
    typename Swap<int,0,1,Container<0,1>>::type::p();
    typename Swap<int,0,1,Container<0,1,2,3>>::type::p();
    typename Swap<int,0,2,Container<0,1,2,3>>::type::p();
    typename Swap<int,0,3,Container<0,1,2,3>>::type::p();
    typename Swap<int,1,2,Container<0,1,2,3>>::type::p();
    typename Swap<int,1,3,Container<0,1,2,3>>::type::p();
    typename Swap<int,2,3,Container<0,1,2,3>>::type::p();
}