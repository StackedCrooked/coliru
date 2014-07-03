#include<algorithm>
#include<list>
#include <iostream>
using std::cout; using std::endl;
template <template <typename, typename...> class container_type> struct SortTraits {

  template <class comparator_type>
  static void sort(container_type<size_t> &front, comparator_type comp) {
    std::sort(front.begin(), front.end(), comp);
  }
};


template <> struct SortTraits<std::list> {

  template <class T, class comparator_type>
  static void sort(std::list<T> &front, comparator_type comp) {
    front.sort(comp);
  }
};

struct MyFunctor {
  bool operator()( const size_t& a, const size_t& b ) const {
    return a>b;
  }
};


int main(int argc, char *argv[]) {

  std::list<size_t> myContainer = {3,5,2,6,3,6,7};

  MyFunctor mySortFunctor;

  SortTraits<std::list>::sort(myContainer, mySortFunctor);

  for (auto it = myContainer.begin(); it != myContainer.end(); ++it)
    cout<<" "<<*it;
  cout<<endl;
  return 0;
}