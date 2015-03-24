#include <iostream>
#include "boost/strong_typedef.hpp"
using namespace std;

BOOST_STRONG_TYPEDEF(int, ancaps)
BOOST_STRONG_TYPEDEF(int, libertarians)
int main() { 
ancaps a{7};
libertarians l{2};
auto result = a/l;
cout << result; 

}
