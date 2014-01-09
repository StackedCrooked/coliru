#include <type_traits>

template <typename T>
class TTest{
public:
  T data;

  template<typename U = T>
  typename std::enable_if<std::is_unsigned<U>::value, bool>::type
  operator !=(const TTest<U>& other) const;

  template<typename U = T>
  typename std::enable_if<not std::is_unsigned<U>::value, bool>::type
  operator !=(const TTest<U>& other) const;
};

template <typename T>
template <typename U>
typename std::enable_if<std::is_unsigned<U>::value, bool>::type
TTest<T>::operator !=(const TTest<U>&) const{
  return true;
}

template <typename T>
template <typename U>
typename std::enable_if<not std::is_unsigned<U>::value, bool>::type
TTest<T>::operator !=(const TTest<U>&) const{
  return false;
}

#include <iostream>

int main(){
  TTest<unsigned> t1,t2;
  TTest<int> t3,t4;
  
  std::cout << (t1 != t2) << '\n';
  std::cout << (t3 != t4) << '\n';
}
