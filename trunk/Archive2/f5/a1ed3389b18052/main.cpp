#include <iostream>
#include <tuple>
using namespace std;
 
template <typename... Args>
struct pack
{
};
 
template <template <typename... Args> class ENCAP, typename... Args>
struct encapsulate_arguments
{
    typedef pack<ENCAP<Args>...> type;
};
 
template <template <typename... Args> class ENCAP, typename... Args>
struct encapsulate_arguments<ENCAP, pack<Args...>>
{
	typedef pack<ENCAP<Args>...> type;
};
 
template <typename L>	
struct Master
{
    template<class>
    using Foo = int;
	template <typename T>
	struct Slave
	{
		typedef T type;	
	};
};

template <typename L>   
struct Other
{
  typedef typename encapsulate_arguments<Master<L>::template Slave, pack<double, int>>::type EmbeddedType;
};
 
int main() {
	encapsulate_arguments<Master<float>::Slave, pack<double, int>>::type foo;
	encapsulate_arguments<Master<float>::Slave, double, int>::type bar;
	return 0;
}