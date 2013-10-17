#include <stdexcept>
#include <iostream>
using namespace std;

int main()
try
{
  int h;
  cin >> h;
  if(cin) cout << "OK ";
  else throw std::runtime_error("NOT AN INT ");
  return 0;
}
catch(exception& e) {
    cout<<e.what();
    return 1;
}
