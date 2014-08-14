#include <cstdlib>
#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;


template <class T>
void cppfilt(const T& t) {
  const std::type_info& ti = typeid(t);
  static const std::string command("c++filt -t ");
  system((command + std::string(ti.name())).c_str());
}

template <typename T>
void print_type(T& t) {
 cout<<"Type: "<<typeid(t).name()<<endl;
}

int main(){

  std::string s("hello world!");
  int v = 5;
  
  cout<<"Pring mangled ty:pes"<<endl;
  print_type(s);
  print_type(v);
  
  
  cout<<"\nDemangle symbols using c++filt"<<endl;
  cppfilt(s);
  cppfilt(v);
  
  return 0;
}