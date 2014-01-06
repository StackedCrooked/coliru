#include <iostream>

int main()
{
    for (int i = 0; i < 3; i++)
        if (i == 2) {
            std::cout << i << '\n';
        }
}template<class T>
class A
{
public:
   A(T t): x(t){}
   T getX();
private:
   T x;
};

template<class T>
T A<T>::getX()
{
   return x;
}

// member function specialization
//template<> // works with and without template<> 
long A<long>::getX()
{
   return 1000L;
}