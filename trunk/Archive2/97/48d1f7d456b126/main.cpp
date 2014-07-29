#include <iostream>
using namespace std;

template<typename T>
struct Recursive
{
    using cycle = struct X : Recursive<X> {};
};


int main() 
{
	Recursive<int> x;

	return 0;
}