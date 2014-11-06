#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>


using namespace std;

int main()
{
   const boost::shared_ptr<int> myInt = boost::make_shared<int>(1);
   
   *myInt = 2;
   
   cout << *myInt << endl;
   return 0;
}
