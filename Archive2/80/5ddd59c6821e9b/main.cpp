
#include <iostream>
#include <algorithm>

template<typename ForwardIterator1, typename ForwardIterator2, typename Func>
  void for_each_intersecting(ForwardIterator1 begin1, ForwardIterator1 end1, ForwardIterator2 begin2, ForwardIterator2 end2, Func what) {
      while( (begin1 != end1) && (begin2 != end2) ) {
          if( *begin1 < *begin2 )
            ++begin1;
          else if( *begin2 < *begin1 )
            ++begin2;
          else
            what(*begin1++, *begin2++);
      }
  }

int main() {
    std::vector<int> v1 { 1, 2, 3, 4, 5, 6, 7, 8 };
    std::vector<int> v2 { 2, 4, 6, 8, 10, 12, 14, 16 };
    for_each_intersecting(v1.begin(), v1.end(), v2.begin(), v2.end(), [](const int& i1, const int& i2) { std::cout << i1 << ' ' << i2 << '\n'; });
}
