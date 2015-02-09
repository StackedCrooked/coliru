#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <iterator>

template<class T>
struct Insert {
  template<class C>
  void into (C& c) && {
    auto pos = std::lower_bound (cont.begin (), cont.end (), _data);
    c.emplace (pos, std::forward<T> (_data));
  }

  T&& _data;
};

template<class T>
Insert<T> insert (T&& e) { return { e }; }

// ---------------------------------------------

int main () {
  std::vector<int> vec;

  for (auto e : {1,9,4,8,5,0,-1,100,5})
    insert (e).into (vec);

  {
    std::copy (
      std::begin (vec), std::end (vec),
      std::ostream_iterator<int> (std::cout, " ")
    );

    std::cout << "\n";
  }
}