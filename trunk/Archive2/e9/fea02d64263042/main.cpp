#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <limits>
#include <climits>

using namespace std;

struct Data{};
struct Val1{};

template <class T>
struct Base{
   template<class Val>
   void do_it(){
   }
};

template <class T = Base<Data> >
struct Concrete: T{      
  void test(){
    typename Concrete:: template do_it<Val1>();         // I want not write "typename Concrete:: template " each time
  }
};


int main()
{
}
