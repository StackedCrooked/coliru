// http://stackoverflow.com/questions/23393958/binary-search-an-object-in-a-sorted-vector-with-some-meaningless-entries-as-inte
#include <iostream> 
#include <algorithm>
#include <vector>
using std::cout;
using std::vector;
using std::find_if;
using std::reverse_iterator;

typedef vector<int>::iterator iter;
typedef reverse_iterator<iter> RIter;
iter first_non_zero( iter first, iter last ) {
    return find_if(first, last, [](int i){return i != 0;} );
}
RIter last_non_zero( iter first, iter last )
{
    auto riter = RIter(last);
    auto rend  = RIter(first);
    return find_if(riter, rend, [](int i){return i != 0;} );
}
iter binary_search( iter first, iter last, int x )
{
    auto it = first_non_zero(first, last);
    if (it == last || *it >= x) return it;
    auto rit = last_non_zero(first, last);
    if (*rit < x) return last;
    if (*rit == x) return --rit.base();
    size_t m = (rit.base() - it) / 2;
    iter mid = it + m;
    auto f = binary_search( it, mid, x );
    return f == mid ? binary_search( mid, rit.base(), x ) : f;
}

int main () {
    vector<int> A{0,0,5,0,6,9,10,21,0,40,0};
    for( int x = 1; x < 42; ++x ) {
        auto i = binary_search( A.begin(), A.end(), x );
        size_t ix = i - A.begin();
        cout << x << " " << ix << "\n";
    }
    return 0;
}