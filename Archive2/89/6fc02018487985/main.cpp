#include <type_traits>

template <typename T>
class TTest{
public:
  T data;
  
  bool operator!=(const TTest& other) const
  {
      return not_equal_to(other, typename std::is_unsigned<T>::type());
  }
  
private:
  bool not_equal_to(TTest const&, std::true_type) const
  {
      return true;
  }
  
  bool not_equal_to(TTest const&, std::false_type) const
  {
      return false;
  }
};

#include <iostream>

int main(){
  TTest<unsigned> t1,t2;
  TTest<int> t3,t4;
  
  std::cout << (t1 != t2) << '\n';
  std::cout << (t3 != t4) << '\n';
}
