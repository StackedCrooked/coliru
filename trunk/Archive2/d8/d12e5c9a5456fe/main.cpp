    // http://stackoverflow.com/questions/23393958/binary-search-an-object-in-a-sorted-vector-with-some-meaningless-entries-as-inte
    #include <iostream> 
    #include <vector>
    using std::vector;

    class z_skip
    : public std::iterator<std::forward_iterator_tag, int>
    {
        vector<int> * _p = nullptr;
        size_t _x = 0;
    public:
        z_skip() = default;
        z_skip(vector<int> & p) : _p(&p) { *this += 0; }
        bool operator!= (const z_skip& other) const { return _p != other._p || _x != other._x; }
        size_t index() const { return _x; }
        int& operator* () { return _p->at(_x); }
        z_skip& operator+=( size_t n ) {
            do {
                if (n) ++_x;
                while( _x < _p->size() && _p->at(_x) == 0 ) ++_x;
            } while (n--);
            if (_x >= _p->size()) { _x = 0; _p = nullptr; }
            return *this;
        }
        z_skip& operator++ () { return *this += 1; }
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