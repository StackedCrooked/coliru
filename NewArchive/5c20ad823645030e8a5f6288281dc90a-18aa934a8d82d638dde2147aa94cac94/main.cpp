#include<iostream>
#include<type_traits>

//apply no longer matches my templates?? 
template<typename Func, typename T>
void apply(Func func_ptr,T x)
{
   func_ptr(x);
}

template<typename T> void single(T)
{

}

template<typename T,
typename = std::enable_if<!std::is_pointer<T>::value, T>::type> 
void multi(T t)
{
   std::cout << t << '\n';
}

template<typename T,
typename = std::enable_if<std::is_pointer<T>::value, T>::type> 
void multi(T* p)
{
   std::cout << *p << '\n';
}

int main()
{
apply(&single<int>, 3); 
apply(&multi<int>, 7);   
int * p = new int;
*p = 55;
apply(&multi<int*>, p);
}