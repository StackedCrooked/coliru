#include <iostream>
 
template <size_t ...ID>
struct index{};

template <size_t NUMBER, size_t ...ID>
struct make_index
{
    typedef typename make_index<NUMBER-1,NUMBER, ID...>::type type;
};

template <size_t ...ID>
struct make_index<0,ID...>
{
	typedef index<0,ID...> type;
};

template <typename T>
bool gun(T val, size_t id)
{
	std::cout<<val<<"(Argument number "<<id<<")"<<std::endl;
	return true;
}

template <typename ...T, size_t ...ID>
void fun(index<ID...> dummy, T... val)
{
	auto init={gun<T>(val, ID)...};
	(void)init;
}

template <typename ...T>
void fun(T... val)
{
	fun(typename make_index<sizeof...(T)-1>::type(),val...);
}
 
int main(int argc, char *argv[])
{
    fun(1,2,3,4.0,5.0f,'6','a',2048,42);
}