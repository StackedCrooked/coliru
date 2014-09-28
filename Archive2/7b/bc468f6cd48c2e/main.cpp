// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>
#include <type_traits>

int dub(int i)
{
    return i * 2;
}

template <typename T>
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
  T p;
public:
  MyIterator(T x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) {return p!=rhs.p;}
  typename std::result_of<decltype(dub)(int)>::type operator*() {return dub(*p);}
  typename std::iterator_traits<T>::difference_type operator- (const MyIterator &rhs) const { return p - rhs.p; }
};

template <typename T>
MyIterator<T> make_myiterator(T t)
{
    return MyIterator<T>(t);
}

int main () {
  int numbers[]={10,20,30,40,50};
  std::vector<int> v(std::begin(numbers), std::end(numbers));
  std::vector<int> num( make_myiterator(v.begin()), make_myiterator(v.end()) );
  
  return 0;
}