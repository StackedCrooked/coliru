
#include <iostream>
#include <algorithm>
#include <functional>

template<typename ForwardIterator1, typename ForwardIterator2, typename Comp, typename Func>
  void for_each_intersecting(ForwardIterator1 begin1, ForwardIterator1 end1, ForwardIterator2 begin2, ForwardIterator2 end2, Comp comp, Func what) {
      while( (begin1 != end1) && (begin2 != end2) ) {
          if( comp(*begin1,*begin2) )
            ++begin1;
          else if( comp(*begin2,*begin1) )
            ++begin2;
          else
            what(*begin1++, *begin2++);
      }
  }
  
struct employee { int id, salary; };

int main() {
    std::vector<employee> v1 { { 1, 1500 }, { 10, 2000 }, { 15, 2500 }, { 16, 1000 } };
    std::vector<employee> v2 { { 10, 1500 }, { 13, 2000 }, { 15, 500 }, { 19, 1300 } };
    for_each_intersecting(v1.begin(), v1.end(), v2.begin(), v2.end(), [](const employee& e1, const employee& e2) { return e1.id < e2.id; },
      [](const employee& e1, const employee& e2) { std::cout << e1.id << ' ' << e2.id << ' ' << e1.salary << ' ' << e2.salary << '\n'; });
}
