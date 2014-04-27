#include <iostream>
using namespace std;

template <int n> 
struct Factorial
{
     static constexpr long double val = n * Factorial<n-1>::val;
};

template <>
struct Factorial<0>
{
	 static constexpr long double val = 1;
};



int main()
{
	cout<<Factorial<7>::val<<endl;
}

