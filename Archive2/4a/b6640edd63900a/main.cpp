#include <iostream>

using namespace std;
using std::enable_if;

template <bool C>
using only_if = typename std::enable_if <C>::type;

template <typename T>
using is_lref = std::is_lvalue_reference <T>;

struct X
{
    template <typename T, typename U>
	static void
	Func3(T& t, U& u) { cout << "X1" << endl; }

	template <typename T, typename U>
	static only_if <!is_lref <T>()>
	Func3(T&& t, U& u) { cout << "X2" << endl; }

	template <typename T, typename U>
	static only_if <!is_lref <U>()>
	Func3(T& t, U&& u) { cout << "X3" << endl; }

	template <typename T, typename U>
	static only_if <!(is_lref <T>() || is_lref <U>())>
	Func3(T&& t, U&& u) { cout << "X4" << endl; }
};

void Func2(int& a, int& b) { cout << "V1" << endl; }
void Func2(int&& a, int& b) { cout << "V2" << endl; }
void Func2(int& a, int&& b) { cout << "V3" << endl; }
void Func2(int&& a, int&& b) { cout << "V4" << endl; }

template < typename T, typename U>
void Func( T&& t, U&& u)
{
    X::Func3( std::forward<T>(t), std::forward<U>(u));
    Func2( std::forward<T>(t), std::forward<U>(u));
}

int main()
{
    int a, b;
    
    Func( a,b);
    Func( 1,b);
    Func( a,2);
    Func( 1,2);

    return 0;
}
