#include <iostream>
using namespace std;
int main() 
{ 
    
  cout<<std::boolalpha << [](){ return 0;};
  cout<<[](){ return 3.2;};
  cout<<[](){ return true;};
  cout<<[](){ return false;};
  cout<<[](){ return "Hello world!";};
  cout<<[]()->int{ return 0;};
  cout<<[]()->double{ return 3.2;};
  cout<<[]()->bool{ return true;};
  cout<<[]()->bool{ return false;};
  cout<<[]()->const char*{ return "Hello world!";};
  return 0;
}