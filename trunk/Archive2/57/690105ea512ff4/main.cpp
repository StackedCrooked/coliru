#include <algorithm>
#include <iterator>
#include <vector>

template<class InputIterator, class T>
bool privIsElementOf(const T& element, InputIterator first, InputIterator last)
{
  return ( std::find(first, last, element) != last );
}

template<class Container, class T>
bool isElementOf(const T& element, const Container & cont)
{
  return privIsElementOf( element, std::begin(cont), std::end(cont) );
}

template<class T>
bool isElementOf(const T& element, const std::initializer_list<T> iList)
{
  return privIsElementOf( element, std::begin(iList), std::end(iList));
}

int main()
{
  std::vector<int> myVec { 1 , 3 , 5};

  bool isElement  = isElementOf(3, myVec);
  bool isElement2 = isElementOf(3, {1 , 3, 5 });
  
  return 0;
}
