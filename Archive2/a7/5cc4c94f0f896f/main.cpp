/** http://informatics.mccme.ru/mod/statements/view3.php?chapterid=2796

    To try:

    $ g++ -std=c++11 *.cpp && echo 1 4 | ./a.out
    1211

    Python equivalent:

      #!/usr/bin/env python2
      from itertools import groupby

      def next_term(x):
          """111 22 1 -> 3'1 2'2 1'1"""
          return ''.join(str(len(list(same))) + digit for digit, same in groupby(x))

      x, n = raw_input().split()
      for _ in range(1, int(n)):
          x = next_term(x)
      print x
*/
#include <algorithm> // min
#include <iostream>
#include <string>

int main() {
  using namespace std;
  string x;
  unsigned short n;
  if(!(cin >> x >> n)) return 1; // error
  for (unsigned short i = 1; i < n; ++i) {
    string y;
    for (size_t pos = 0; pos < x.size(); ) {
      const size_t not_same_pos = x.find_first_not_of(x[pos], pos+1);
      y += to_string(min(not_same_pos, x.size()) - pos) + x[pos];
      pos = not_same_pos;
    }
    swap(x, y);
  }
  if (!(cout << x << endl)) return 1; // error
}