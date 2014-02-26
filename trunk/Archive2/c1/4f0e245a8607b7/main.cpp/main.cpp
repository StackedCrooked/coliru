#include <iostream>

using namespace std;

template <typename Obj, typename T>
void fun_impl(const Obj& obj, const T& x)
{
    cout << x << endl;
}

template <typename Obj, typename T, size_t N>
void fun_impl(const Obj& obj, const T (&x)[N])
{
	for (auto& a : x)
		cout << a << " ";
	cout << endl;
}

template <typename Obj>
void fun(const Obj& obj)
{
   fun_impl(obj, obj.x);
}

struct I { int x; };
struct A { int x[4]; };

int main ()
{
	fun(I{4});
	fun(A{{1, 2, 3, 4}});
}
