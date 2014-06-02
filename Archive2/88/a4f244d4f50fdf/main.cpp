#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <limits>
#include <climits>

using namespace std;

struct Data{};
struct Val1{};

template<typename T> struct type2type { typedef T type; };

template <class T>
struct Base{
   template<class U>
   void do_it(const U& type){
       typedef typename U::type actual_type;
       actual_type x;
   }
};

template <class T = Base<Data> >
struct Concrete: T{      
  void test(){
    this->do_it(type2type<Val1>());         // I want not write "typename Concrete:: template " each time
  }
};

int main()
{
    Concrete<> x;
    x.test();
}
