// http://stackoverflow.com/questions/23393958/binary-search-an-object-in-a-sorted-vector-with-some-meaningless-entries-as-inte
#include <iostream> 
#include <algorithm>
#include <vector>
using std::cout;
using std::vector;
using std::find_if;
using std::reverse_iterator;
using std::lower_bound;

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

    class iterator
    : public std::iterator<std::forward_iterator_tag, int>
    {
        vector<int> * _tp = nullptr;
        size_t _x = 0;
    public:
        iterator() = default;
        iterator(vector<int> & tp) : _tp(&tp) {}
        bool operator!= (const iterator& other) const {
            return _tp != other._tp || _x != other._x;
        }
        int & operator* () { nonzero(); return _tp->at(_x); }
        int * operator->() { nonzero(); return &_tp->at(_x); }
        void nonzero() { while( ++_x < _tp->size() && _tp->at(_x) == 0 ); }
        iterator& operator++ () {
            nonzero();
            if (++_x >= _tp->size()) {
                _x = 0;
                _tp = nullptr;
            }
            return *this;
        }
        iterator& operator+= ( size_t x ) { while(x--) _x++; return *this; }
        friend inline iterator& operator+ ( iterator & lhs, size_t x ) { while(x--) ++lhs; return lhs; }
        friend inline iterator operator+ ( iterator lhs, size_t x ) { while(x--) ++lhs; return lhs; }
        friend inline size_t operator-( const iterator & x, const iterator & y ) { return y._x - x._x; }
    };
    inline iterator begin(vector<int> & A) { return iterator(A); }
    static inline const iterator end() { return iterator(); }

int main () {
    vector<int> A{0,0,5,0,6,9,10,21,0,40,0};
    for( int x = 1; x < 42; ++x ) {
        iterator i = lower_bound<iterator,int>( iterator(A), iterator(), x );
        size_t ix = i - iterator(A);
        cout << x << " " << ix << "\n";
    }
    return 0;
}