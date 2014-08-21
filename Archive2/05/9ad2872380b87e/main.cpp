#include <iostream>

template<typename T, typename U> //Primary
struct test
{
   void foo() { std::cout << "\nPrimary"; }
};

template <typename T> //Specialization
struct test<T, int*>
{
   void foo() { std::cout << "\nPartial Specialization"; }
};


template<> //Full specialization
struct test<int*, int*>
{
   void foo() { std::cout << "\nFull Specialization"; }
};

int main()
{
    test<int, double> t1;
    t1.foo();
    
    test<double, int*> t2;
    t2.foo();
    
    test<int*, int*> t3;
    t3.foo();
}