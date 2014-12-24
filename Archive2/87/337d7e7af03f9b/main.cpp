#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include <ctime>
#include <stdexcept>
#include <type_traits>

struct A {
   A() = default;
   A(A &&) = delete;
   A & operator = (A &&) = delete;
};

struct B {
   int n = 42;
   B() = default;
   B(B const &) = default;
   //B & operator = (B const&) = default;// {return *this;}
};

struct C {
   C() = default;
   C(C &&) = default;
   B a;
};

int main()
{
   std::cout << std::boolalpha;
   std::cout << "is_move_assignable:" << std::endl;
   std::cout << "A: " << std::is_move_assignable<A>::value << std::endl;
   std::cout << "B: " << std::is_move_assignable<B>::value << std::endl;

   B b;
   B b2 = std::move(b);


   return 0;
}
