#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& out, T const &x);

template<typename T, typename K>
struct A{
  friend std::ostream& operator<<<K>(std::ostream& out, K const &x);
};
 
template<typename T>
std::ostream& operator<<(std::ostream& out, T const &x) {
  (void) x; // to silent the compiler
  // ...
  return out;
}
 
int main(){
   A<int,int> i;
   A<double,int> j;
   
   (void) i;
   (void) j;
}