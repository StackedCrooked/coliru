#include <iostream>

template<int I> 
int fibo()
{
    return fibo<I-1>()+fibo<I-2>();
}

template<>
int fibo<1>()
{
    return 1;
}

template<>
int fibo<0>()
{
    return 0;
}
/*template<>  // explicit specialization for T = void
struct is_void<void> : std::true_type
{
};*/
int main()
{
    // for any type T other than void, the 
    // class is derived from false_type
    /*std::cout << std::boolalpha<<is_void<char>::value << '\n'; */
    // but when T is void, the class is derived
    // from true_type
    std::cout << fibo<12>()<< '\n';
}