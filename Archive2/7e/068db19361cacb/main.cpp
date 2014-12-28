#include<iostream>

template<typename T>
struct Pair
{
	template<typename T1>
    Pair<T>& operator=(Pair<T1>&)
    {
        std::cout << "Templated assignment operator called";
        return *this;
    }
};

int main()
{
	Pair<int> P1, P2;
	P2=P1;
}