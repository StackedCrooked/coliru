#include <algorithm>
#include <iterator>

template<class It>
bool
foo (It beg, It end) {
  using namespace std;

  if (beg == end || next (beg) == end || *beg == *next (beg))
    return false;

  return mismatch (next (beg, 2), end, beg).first == end;
}



/***************************************************************************/

#include <iostream>

template<class T>
void
check (T const& data)
{
  using std::begin;
  using std::end;

  std::cout << foo (begin (data), end (data)) << " <= ";

  std::copy (begin(data), end(data),
    std::ostream_iterator<typename std::iterator_traits<decltype(begin(data))>::value_type> (std::cout, " ")
  );

  std::cout << "\n";
}

int main () {
  check (std::vector<int> {});
  check (std::vector<int> {1});
  check (std::vector<int> {1,2,3});
  check (std::vector<int> {1,2,1,2,2});
  check (std::vector<int> {1,1});
  check (std::vector<int> {1,2,1});
  check (std::vector<int> {1,2,1,2});
  check (std::vector<int> {1,2});
}