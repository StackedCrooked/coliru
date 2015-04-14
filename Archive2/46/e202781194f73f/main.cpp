#include <iostream>

template<class Ty>
struct OP
{	
	void operator()(Ty Ptr) const noexcept
	{	
        std::cout << "single pointer\n"; 
		delete Ptr;
	}
};

template<class Ty, std::size_t N>
struct OP<Ty[N]>
{
	void operator()(Ty* Ptr) const noexcept
	{
        std::cout << "dynamically allocated array\n"; 
		delete[] Ptr;
	}
};

template<typename T>
void f1(T arg)
{
   OP<T>()(arg); 
}


int main()
{
     f1(new int(3));  
     f1<int[3]>(new int[(3)]);  
}
