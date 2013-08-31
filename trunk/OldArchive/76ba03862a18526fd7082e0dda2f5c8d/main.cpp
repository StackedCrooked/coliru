#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <array>

template<typename T>
struct is_polymorphic_functor
{
private:
    //test if type U has operator()(V)
    template<typename U, typename V>
    static auto ftest(U *u, V* v) -> decltype((*u)(*v), char(0));
    
    static std::array<char, 2> ftest(...);

    struct private_type { };

public:
    static const bool value = sizeof(ftest((T*)nullptr, (private_type*)nullptr)) == 1;
};


//non-polymorphic functor
template<typename T> struct X { void operator()(T) {} };

//polymorphic functor 
struct Y { template<typename T> void operator()(T) {} };

//MORE
struct nonpolymorphic1 { void operator()(int) {} };
template<typename T> struct nonpolymorphic2 { void operator()(T) {} };
template<typename T, typename U> struct nonpolymorphic3 { void operator()(T,U) {} };

struct polymorphic1 { template<typename T> void operator()(T) {} };
struct polymorphic2 { template<typename T> void operator()(int, T) {} };
struct polymorphic3 { template<typename T, typename U> void operator()(T, U) {} };

#define print(a)  std::cout << #a << " = " << a << std::endl

int main() 
{
    print (( is_polymorphic_functor<X<int>>::value ));
    print (( is_polymorphic_functor<Y>::value ));
    print (( is_polymorphic_functor<nonpolymorphic1>::value )) ;
	print (( is_polymorphic_functor<nonpolymorphic2<int>>::value )) ;
	print (( is_polymorphic_functor<nonpolymorphic3<int,short>>::value )) ;
	print (( is_polymorphic_functor<polymorphic1>::value )) ;
	print (( is_polymorphic_functor<polymorphic2>::value )) ;
	print (( is_polymorphic_functor<polymorphic3>::value )) ;

}