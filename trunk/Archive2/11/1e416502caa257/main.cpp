    // http://stackoverflow.com/questions/23393958/binary-search-an-object-in-a-sorted-vector-with-some-meaningless-entries-as-inte
    #include <iostream> 
    #include <vector>
    using std::vector;

    class z_skip
    : public std::iterator<std::forward_iterator_tag, int>
    {
        vector<int> * _tp = nullptr;
        size_t _x = 0;
    public:
        z_skip() = default;
        z_skip(vector<int> & tp) : _tp(&tp) { skip_zeros(); }
        bool operator!= (const z_skip& other) const {
            return _tp != other._tp || _x != other._x;
        }
        size_t index() const { return _x; }
        int & operator* () { return _tp->at(_x); }
        int * operator->() { return &_tp->at(_x); }
        void skip_zeros( size_t n = 0 ) {
            do {
                if (n) ++_x;
                while( _x < _tp->size() && _tp->at(_x) == 0 ) ++_x;
            } while (n--);
            if (_x >= _tp->size()) {
                _x = 0;
                _tp = nullptr;
            }
        }
        z_skip& operator++ () { skip_zeros(1); return *this; }
    };

    int main () {
        vector<int> A{0,0,5,0,6,9,10,21,0,40,0};
        for( int x = 1; x < 42; ++x ) {
            auto i = std::lower_bound( z_skip(A), z_skip(), x );
            if (i != z_skip()) std::cout << x << " " << i.index() << "\n";
            else std::cout << x << " end()\n";
        }
        return 0;
    }
