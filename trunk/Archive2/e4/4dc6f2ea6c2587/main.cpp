#include <type_traits>
#include <iostream>

using namespace std;

template<typename T, size_t N>
struct X
{
    T a[N];
	
	X() : a{} { }

	template<typename... A>
	explicit X(A&&... a) : a{std::forward<A>(a)...} { }
};

template<typename T, size_t N>
struct Y : X<T,N>
{
	explicit Y() : X<T,N>{} { }

	template<typename... A>
	explicit Y(A&&... a) : X<T,N>{std::forward<A>(a)...} { }
};



int main ()
{
	Y<int,3> x;
	Y<Y<int,3>,4> y{x,x};
}
