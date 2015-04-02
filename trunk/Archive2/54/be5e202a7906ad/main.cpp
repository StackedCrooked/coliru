#include <iostream>
#include <quadmath.h>

using namespace std;

int main(){
  __float128 r=0.0q;
  __float128 exp_d = expq(12.45q);

  cout << "r=" << (double)r << endl;
  cout << "exp_d=" << (double)exp_d << endl;
}
