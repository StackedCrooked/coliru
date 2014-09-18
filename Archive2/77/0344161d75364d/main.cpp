#include <type_traits>
#include <iostream>
#include <vector>

template <typename T>
struct is_cont
{
    static const bool value = false;
};

template <typename T,typename Alloc>
struct is_cont<std::vector<T,Alloc> >
{
	static const bool value = true;
};

template<typename T , typename std::enable_if<is_cont<T>::value , T>::type = {}>
void Moo (T t)
{
	std::cout << "YAY!" << std::endl;
}

template<typename T , typename std::enable_if<!is_cont<T>::value , T>::type = {}>
void Moo (T t)
{
	std::cout << "MOO!" << std::endl;
}

int main() {
	// foo<std::array<int , 2>> ();
	int test;
	std::vector<int> test2;
	// Moo (test);
	Moo (test2);
	std::cout << is_cont<std::vector<int>>::value << std::endl;
	return 0;
}