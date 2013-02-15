#include <iostream>

struct A
{
    template<unsigned int> struct D;
};
template<> struct A::D<0> { };
template<> struct A::D<1> { };

struct B
{
    template<unsigned int> struct D;
};
template<> struct B::D<0> { };
template<> struct B::D<1> { };
template<> struct B::D<2> { };


template<class T>
struct highest_index
{
    private:
		template<int i>
		struct is_defined {};

		template<int i>
                static char f(is_defined<sizeof(typename T::template D<i>)> *);

		template<int i>
		static int f(...);

                template<int i>
		struct get_index;

		template<bool b, int j>
		struct next
		{
			static const int value = get_index<j>::value;
		};
		template<int j>
		struct next<false, j>
		{
			static const int value = j-2;
		};
		template<int i>
		struct get_index
		{
			static const bool exists = sizeof(f<i>(0)) == sizeof(char);
			static const int value = next<exists, i+1>::value;
		};

	public:
		static const int index = get_index<0>::value; 
};

int main()
{
	std::cout << highest_index<A>::index << std::endl;
	std::cout << highest_index<B>::index << std::endl;
}

