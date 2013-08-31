#include <vector>
#include <algorithm>
#include <iostream>
#include <boost/phoenix/phoenix.hpp>

namespace phx = boost::phoenix;

struct myClass
{
   int i;

   int getNumber() const { return i; }
   void setNumber(int j) { i = j; }
};

using namespace boost::phoenix::arg_names;
static const auto getNumber = phx::lambda [ phx::bind(&myClass::getNumber, arg1) ];

int main()
{
   const std::vector<myClass*> vect { new myClass{1}, new myClass{2}, new myClass{42} };
   std::vector<int> numVect(vect.size());

   // just bind:
   std::transform (vect.begin(), vect.end(), numVect.begin(), phx::bind(&myClass::getNumber, arg1));

   // using more natural syntax
   std::transform (vect.begin(), vect.end(), numVect.begin(), getNumber(arg1));

   for(auto i : numVect)
       std::cout << i << " ";
}
