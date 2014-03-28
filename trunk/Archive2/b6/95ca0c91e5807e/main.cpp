#include <typeinfo>
#include <iostream>
#include <functional>
using namespace std;

using FuncPtr = void(*)(int);

template<typename T>
void Fun(T& t);

template<typename T>
void Fun(T* t);

auto Glambda = [](auto a_){ cout << a_ << endl;};

template<>
void Fun<>(function<void(int)>& function_)
{
   function_(42);
}

template<>
void Fun<>(FuncPtr funptr_)
{
   funptr_(142);
}

template<>
void Fun<>(decltype((Glambda)) a_)
{
   a_(42);
   a_(3.14);
   a_("it's fun! loving it!");
}

void test()
{
   int local;
   auto LocalGlambda = [](auto){}; // New type
   // Fun(LocalGlambda); Can't instantiate new Fun function type due to no definition.
   Fun(Glambda);

   // FuncPtr fptr = [local](auto a){cout << a << endl;}; //Not a ptr to func
   FuncPtr fptr = [](auto a){cout << a << endl;};
   Fun(fptr);

   function<void(int)> funcTion = [](auto a){ cout << a << endl;};
   function<void(int)> funcTion2 = [local](auto a){ cout << a << endl;};
   Fun(funcTion);
   Fun(funcTion2);
}

int main()
{
   test();
}
