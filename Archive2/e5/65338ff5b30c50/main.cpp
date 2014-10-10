#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

template
<
  typename Fst,
  typename Snd
>
ostream& operator<< (ostream& os, pair<Fst, Snd> const& p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

template
<
  typename Iter,
  typename Ostream
>
void print_range(Iter first, Iter last, Ostream& os) {
  typedef typename Iter::value_type value_type;
  for_each(first, last,
    [&os](value_type const& v) {
      os << "[" << v << ", " << "]";
    });
}

template
<
  typename Key,
  typename Val
>
ostream& operator<< (ostream& os, map<Key, Val> const& m) {
  print_range(m.cbegin(), m.cend(), os);
  return os;
}

template
<
  typename K,
  typename V
>
void print() {}

int main()
{
  pair<int, int> p(1,2);
  map<int, int> m;
  m.insert(p);
  cout << m << endl;
    

}
