// http://stackoverflow.com/questions/23393958/binary-search-an-object-in-a-sorted-vector-with-some-meaningless-entries-as-inte
#include <iostream> 
#include <algorithm>
#include <vector>
using std::cout;
using std::vector;
using std::find_if;
using std::lower_bound;

    class iterator
    : public std::iterator<std::forward_iterator_tag, int>
    {
        vector<int> * _tp = nullptr;
        size_t _x = 0;
    public:
        iterator() = default;
        iterator(vector<int> & tp) : _tp(&tp) {nonzero();}
        bool operator!= (const iterator& other) const {
            std::cerr << "compare " << *this << " and " << other << std::endl;
            return _tp != other._tp || _x != other._x;
        }
        size_t index() const { return _x; }
        int & operator* () { return _tp->at(_x); }
        int * operator->() { return &_tp->at(_x); }
        void nonzero( size_t n = 0 ) {
            _x += n;
            while( _x < _tp->size() && _tp->at(_x) == 0 ) ++_x;
            if (_x >= _tp->size()) {
                _x = 0;
                _tp = nullptr;
            }
            std::cout << "nonzero: " << (_tp ? int(_x) : -1) << std::endl;
        }
        iterator& operator++ () { nonzero(1); return *this; }
        friend std::ostream& operator<<(std::ostream &s, const iterator & rhs ) { s << rhs._tp << "," << rhs._x; return s; }
    };
    inline iterator begin(vector<int> & A) { return iterator(A); }
    static inline const iterator end() { return iterator(); }

int main () {
    vector<int> A{0,0,5,0,6,9,10,21,0,40,0};
    for( int x = 1; x < 42; ++x ) {
        auto begin = iterator(A);
        auto end = iterator();
        iterator i = lower_bound( begin, end, x );
        cout << x << " " << i.index() << "\n";
    }
    return 0;
}