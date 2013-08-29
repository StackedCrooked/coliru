#include <iostream>
template<int N>
struct NumberGeneration{
  static void out(std::ostream& os)
  {
    NumberGeneration<N-1>::out(os);
    os << N << std::endl;
  }
};
template<>
struct NumberGeneration<1>{
  static void out(std::ostream& os)
  {
    os << 1 << std::endl;
  }
};
int main(){
   NumberGeneration<1000>::out(std::cout);
}