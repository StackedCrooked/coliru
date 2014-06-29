#include <boost/phoenix.hpp>
#include <iostream>
#include <ostream>

using namespace std;
using namespace boost;
using namespace phoenix;
using namespace arg_names;
using namespace local_names;


struct FakeOne{
    int field;    
};

int main()
{
    auto k = FakeOne();    

    auto fn = (lambda(_a=k)[_a.field ]);
   cout <<
      fn()
   << endl;

}