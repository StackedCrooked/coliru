#include <tuple>
using namespace std;


// http://en.wikipedia.org/wiki/Trie
struct A{}; struct t{}; struct e{}; struct a{};
struct n{}; struct d{}; struct o{}; struct i{};


// A trie for keys "A", "to", "tea", "ted", "ten", "i", "in", and "inn".
using trie = tuple<A,
                   tuple<t,
                         tuple<e,
                               tuple<a,
                                     n,
                                     d>>,
                               o>,
                   tuple<i, n, n>>;
   