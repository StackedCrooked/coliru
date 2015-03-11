#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
//#include <boost/tuple/tuple_comparison.hpp>

typedef boost::tuple<int,int,int> tuple_int;

bool operator==(const tuple_int&, const tuple_int&){
  return true;    
}

struct tuple_int_finder{
  tuple_int_finder(const tuple_int& t) : ti(t) { }
  const tuple_int& ti;
  bool operator()(const tuple_int& lhs) const { return lhs == ti; }    
};

using namespace std;
using namespace boost;

int main(){
  tuple_int t0, t1, t2;
  cout << "t0: " << t0 << ", t1: " << t1 << ", t2: " << t2 << endl;
  
  vector<tuple_int> v;
  v.push_back(t0);
  v.push_back(t1);
  v.push_back(t2);
  
  if(t0 == t2)
    cout << "t0 equals t2" << endl;
  
  if(find_if(v.begin(), v.end(), tuple_int_finder(t0)) != v.end())
    cout << "t0 found!" << endl;
}
