#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>

typedef boost::tuple<int> tuple_int;

bool operator==(const boost::tuple<int>&, const boost::tuple<int>&){
  return false;    
}

int main(){
  tuple_int t, u;
  
  std::vector<boost::tuple<int> > v;
  
  std::cout << std::boolalpha << (t == u) << std::endl;
  
  find(v.begin(), v.end(), t);
}
