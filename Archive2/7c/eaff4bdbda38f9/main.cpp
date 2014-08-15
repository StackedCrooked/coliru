#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

#define N 10


int main(){

std::vector<std::string > s =  {{"##########"},
  {"#@       #"},
  {"#        #"},
  {"#        #"},
  {"#        #"},
  {"#        #"},
  {"#        #"},
  {"#        #"},
  {"#        #"},
  {"##########"}};
  
  for (auto i : s)
      cout<<i<<endl;
  
  cout<<"\nGet @ symbol:"<<s[1][1]<<endl;
  
  return 0;
}