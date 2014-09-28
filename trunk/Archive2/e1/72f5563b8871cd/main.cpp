// std::iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <vector>
#include <type_traits>

int dub(int i)
{
    return i * 2;
}

template <typename T, typename Func>
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
  T p;
  Func func;
public:
  MyIterator(T x, Func f) :p(x), func(f) {}
  MyIterator(const MyIterator& mit) : p(mit.p), func(mit.func) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) {return p!=rhs.p;}
  typename std::result_of<const Func(typename std::iterator_traits<T>::reference)>::type operator*() {
      return func(*p);
     }
  typename std::iterator_traits<T>::difference_type operator- (const MyIterator &rhs) const { return p - rhs.p; }
};

template <typename T, typename Func>
MyIterator<T, Func> make_myiterator(T t, Func func)
{
    return MyIterator<T, Func>(t, func);
}

int main () {
  int numbers[]={10,20,30,40,50};
  std::vector<int> v(std::begin(numbers), std::end(numbers));
  std::vector<int> num( make_myiterator(v.begin(), dub), make_myiterator(v.end(), dub) );
  for (auto it = num.begin(); it != num.end(); ++it)
    std::cout << *it << " ";
  return 0;
}