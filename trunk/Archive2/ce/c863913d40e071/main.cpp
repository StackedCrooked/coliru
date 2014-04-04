#include <iostream>

using namespace std;

template <typename ValueType, ValueType value_>
struct generic_value
{ static ValueType value; };

template <typename ValueType, ValueType value_>
ValueType generic_value<ValueType,value_>::value = value_; // initialize static template-class member

//////////

int f() { return 1111; }
float g() { return 2.22; }



template <typename T>
struct B
{};

template <>
struct B<float>
{
   static auto constexpr funptr = &g; // this only works withh gcc, not with any VS version
   typedef generic_value<decltype(&g),&g> func_ptr_type;
};

template <>
struct B<int>
{
   static auto constexpr funptr = &f;
   typedef generic_value<decltype(&f),&f> func_ptr_type;
};



int main()
{
   std::cout << B<float>::func_ptr_type::value() << std::endl;
   std::cout << B<int>::func_ptr_type::value() << std::endl;
   std::cout << B<short>::func_ptr_type::value() << std::endl;

   std::cout << B<short>::funptr() << std::endl;
   std::cout << B<float>::funptr() << std::endl;
   std::cout << B<int>::funptr() << std::endl;

   return 0;
}