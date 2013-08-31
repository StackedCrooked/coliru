#include <iostream>
#include <tuple>
using namespace std;

template<typename ...T> void sink(T...) {}

class A
{
public:
   template <class... Func>
   void operator()(Func ... func)
   {
     sink( (func(),0)... );
   }
};

int main()
{
    auto f1 = [](){ cout << "return \"Nawaz\"" << endl; return "Nawaz";};
    auto f2 = [](){ cout << "return 100" << endl; return 100;};
    auto f3 = [](){ cout << "return void" << endl; return;};

    A a;
    a(f1, f2, f3);
}