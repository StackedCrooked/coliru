#include <iostream>
    
using namespace std;

template<typename... Args>
void test();

template<typename Aux_type>
void test_helper()
{}

template<typename Aux_type, typename Head, typename... Tail>
void test_helper() {
   cout << Head::i;
   test_helper<Aux_type, Tail...>();
}

template<typename... Args>
void test()
{
    test_helper<void, Args...>();
}

struct A{
   static const int i=1;
};
 
struct B{
   static const int i=2;
};

int main() {
   test<A, B>();
   return 0;
}