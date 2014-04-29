#include <iostream>
#include <memory>
#include <tuple>


using namespace std;

template<int j, int k>
struct Foo
{
};

template<typename T>
struct Z
{
   static int value(const T& t)
   {
       return 0; 
   }
};

template<int ... Ts>
struct Z< Foo<Ts...> >
{
   static int value(const Foo<Ts...>&)
   {
       return 2; 
   }
};

template<typename T>
int Value(const T& obj)
{
   return Z<T>::value(obj);
}

int main()
{
   typedef Foo<2,3> FT;
  
   FT f;

   cout << Value(f) << endl;

   return 0;
}
