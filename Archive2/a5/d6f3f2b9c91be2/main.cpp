#include <tuple>
#include <iostream>

template<std::size_t...> struct seq{};

template<std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};

template<std::size_t... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<typename T>
class thing;

template<typename Value, typename ...Args>
class thing <Value(Args...)> {
public:
    /* moar code */
    template<typename C, size_t... indices>
    void method(C* object, Value(C::*func)(Args...), std::tuple<Args...>&& args, seq<indices...>)
    {
       (object->*func)(std::forward<typename std::tuple_element<indices, std::tuple<Args>>::type>(std::get<indices>(args))...);
    }

    template<typename C> 
    void method(C* object, Value(C::*func)(Args...), Args&&... args) 
    {
       method(object, func, std::forward_as_tuple(args...), gen_seq<sizeof...(Args)>{});
    }
};

struct A
{
   void print() { std::cout << "empty" << std::endl; }
   void print(int value) { std::cout << value << std::endl; }
};

int main()
{
   thing<void()> thing1;
   A a;
   thing1.method(&a, &A::print);

   thing<void(int)> thing2;
   thing2.method(&a, &A::print, 5);
}