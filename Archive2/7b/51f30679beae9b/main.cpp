#include <iostream>
#include <vector>
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>

using namespace std;

template <typename T>
string ContainerToString(const T &input, boost::function<string(typename T::value_type)> to_string_func) 
{
   vector<string> rval;
   for(typename T::const_iterator value=input.begin(); value != input.end(); ++value)
   {
      rval.push_back( to_string_func(*value) );
   }

   return "[" + boost::algorithm::join(rval, ", ") + "]";
}

class MyVariant {
public:
  MyVariant() { }
  MyVariant(const string &s) : m_value(s) { }
  string ToString() const { return m_value; }
  
private:
  string m_value;
};
    
typedef vector<MyVariant> VariantVector;
typedef map<string, MyVariant> VariantMap;

string VectorToString(const VariantVector &input) {
   return ContainerToString(input, boost::function<string(VariantVector::value_type)>(boost::bind(&MyVariant::ToString, _1)));
}

string MapToString(const VariantMap &input) {
   boost::function<string(VariantMap::value_type)> func = [](VariantMap::value_type v){ return v.first + " => " + v.second.ToString(); };
   return ContainerToString(input, func);
}

int main() {
	VariantVector v;
	v.push_back( MyVariant("1") );
	v.push_back( MyVariant("2") );
	v.push_back( MyVariant("3") );
	
	cout << VectorToString(v) << endl;
	
	VariantMap m;
	m["1"] = MyVariant("one");
	m["2"] = MyVariant("two");
	m["3"] = MyVariant("three");
	
	cout << MapToString(m) << endl;
	return 0;
}