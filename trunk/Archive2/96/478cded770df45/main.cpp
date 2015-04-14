#include <iostream>

template<class _Ty>
struct OP
{	
	void operator()(_Ty *_Ptr) const noexcept
	{	
        std::cout << "single pointer\n"; 
		delete _Ptr;
	}
};

template<class _Ty>
struct OP<_Ty[]>
{
	void operator()(_Ty *_Ptr) const noexcept
	{
        std::cout << "dynamically allocated array\n"; 
		delete[] _Ptr;
	}
};

template<typename T>
void f1(T *arg)
{
   OP<T>()(arg); 
}


int main()
{
     f1(new int(3));  
     f1(new int[(3)]);  
}
