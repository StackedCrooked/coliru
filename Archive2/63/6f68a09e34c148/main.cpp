#include <iostream>
#include <type_traits>

template<typename T>
using value_type =  typename std::enable_if<
                    std::is_same<float, T>::value ||
                    std::is_same<double, T>::value
                >::type  ;
                


template<class T, class Enable = void>
class  MyClass2 ;

template<class T>
class MyClass2<T,   value_type<T> > 
{
};


int main()
{
     MyClass2<float> t;
     MyClass2<int> t1; // Errors
}

