#include<iostream>

template<typename T>  // unqualified-id
class foo
{
public:
   typedef T myfoo;
   typedef typename T::type type;
};

// typename followed by a qualified-id denotes the type in a non-type 136 parameter-declaration. (14.1)

// is non-type parameter declaration like the above typedef type defintion or the below

template<int N> // non-type?
class careless
{

};

struct bar
{
  typedef int type;   

};

struct zoo
{
   typedef long type;
};


int main()
{
 foo<bar> f;
 f::type t; //how do you get internal typedef type on f?
}
