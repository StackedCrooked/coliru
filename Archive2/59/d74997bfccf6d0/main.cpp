namespace impl { template<int> struct hack { }; }
#define RefpConcept impl::hack< __LINE__ > * = nullptr

// ---------------------------------------------------------------------

#include <iostream>
#include <type_traits>


template<class Pred, class T = void>
using enable_if_pred = typename std::enable_if<Pred::value, T>::type;

// ---------------------------------------------------------------------

template<class T, class = enable_if_pred<std::is_integral<T>>>
using Integral_t = T;

template<class T, class = enable_if_pred<std::is_floating_point<T>>>
using Floating_t = T;

// ---------------------------------------------------------------------

template<class T, RefpConcept>
void func (Integral_t<T> value) { 
  std::cerr << "integral: " << value << std::endl;
}

template<class T, RefpConcept>
void func (Floating_t<T> value) {
  std::cerr << "floating: " << value << std::endl;
}

int main () {
  func (int    {1234});
  func (char   { 'A'});
  func (float  {1.2f});
  func (double {3.14});
}