#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <deque>
#include <set>

class A
{

};

class B :public A
{

};
template <typename T> class remove_all_pointers{
public:
    using type=T;
};

template <typename T> class remove_all_pointers<T*>{
public:
	typedef typename remove_all_pointers<T>::type type;
};

template <typename T> class remove_all_pointers<T* const>{
public:
	typedef typename remove_all_pointers<T>::type type;
};

template <typename T> class remove_all_pointers<T* volatile>{
public:
	typedef typename remove_all_pointers<T>::type type;
};

template <typename T> class remove_all_pointers<T* const volatile >{
public:
	typedef typename remove_all_pointers<T>::type type;
};

int main()
{
	A* a;
	B* b;
	
	std::cout << std::is_base_of<remove_all_pointers<decltype(a)>::type,
		remove_all_pointers<decltype(b)>::type>::value;
}

