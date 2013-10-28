#include <iostream>
#include <cinttypes>

using namespace std;

int main(){
  const unsigned int b = 100000;
  uint64_t c = 100000;
  cout << (c>>64) << std::endl ;
  cout << (b>> b) ;
  /*b = b >> b;
  cout << b << endl;
  b >>= b;
  cout << b << endl;*/
  return 0;
}