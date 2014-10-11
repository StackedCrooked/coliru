// Type your code here, or load an example.
#include <iostream>
//#include <boost/utility.hpp>
#include <boost/type_traits.hpp>

using namespace std;


struct A{};
struct B : public A {};
struct C {};

template <class T>
string foo()
{
  bool b = boost::is_base_of<A, T>::value;
  if (b)
    return "not derived";
  else
    return "derived";
}

int main() {
    // your code goes here
  cout << foo<B>() << endl;
  cout << foo<C>() << endl;
	return 0;
}
