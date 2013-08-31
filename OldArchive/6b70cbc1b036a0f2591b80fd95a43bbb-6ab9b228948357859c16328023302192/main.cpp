#include <string>
#include <iostream>
using namespace std;

struct Kitty {
  string s;
  friend Kitty operator > (string lhs, Kitty rhs) { rhs.s = move(lhs); return rhs; }
  string operator < (string rhs) const { 
    auto it = begin(rhs);
    auto its = begin(s);
    while (it != end(rhs) && its != end(s)) {
      ++it; 
      it = rhs.insert(it, *(its++));
      ++it;
    }        
    rhs.append(its, end(s));
    return rhs;
  }
} _;

int main(){
  auto x = "cat" >_< "meow";
  cout << x << '\n';
}
