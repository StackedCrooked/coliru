    // http://stackoverflow.com/questions/23393958/binary-search-an-object-in-a-sorted-vector-with-some-meaningless-entries-as-inte
    #include <iostream> 
    #include <vector>
    #include <chrono>

    using std::vector;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    using std::chrono::steady_clock;

    class z_skip
    : public std::iterator<std::random_access_iterator_tag, int>
    {
        vector<int> * _p = nullptr;
        size_t _x = 0;
        size_t * _refs = nullptr;
        size_t * _incs = nullptr;
    public:
        z_skip() = default;
        z_skip(vector<int> & p, size_t& refs, size_t& incs) : _p(&p), _refs(&refs), _incs(&incs) { *this += 0; }
        bool operator!= (const z_skip& other) const { return _p != other._p || _x != other._x; }
        size_t index() const { return _x; }
        int& operator* () { ++*_refs; return _p->at(_x); }
        z_skip& operator+=( size_t n ) {
            *_incs += n+1;
            do {
                if (n) ++_x;
                while( _x < _p->size() && **this == 0 ) ++_x;
            } while (n--);
            if (_x >= _p->size()) { _x = 0; _p = nullptr; }
            return *this;
        }
        z_skip& operator++ () { return *this += 1; }
        ptrdiff_t operator- ( const z_skip & rhs ) const { std::cout << this << "," << &rhs << "," << _x << "," << rhs._x << "\n"; return _x - rhs._x; }
    };

    int main () {
        struct gen_rand { int operator()(){ return rand(); } };
        for( size_t N = 32; N <= 64; N*=2 ) {
            vector<int> A(N);
            for( int i=0; i < N; ++i ) A[i] = i+1;
            if (false) for( int i=0; i < N/64; ++i ) {
                A.insert( A.begin() + A.size() * rand() / RAND_MAX, size_t(N/12) * rand() / RAND_MAX, 0 );
            }

            steady_clock::time_point start = steady_clock::now();

            size_t refs = 0;
            size_t incs = 0;
            for( int x = 1; x <= N+1; ++x ) {
                auto i = std::lower_bound( z_skip(A,refs,incs), z_skip(), x );
                if (i != z_skip()) std::cout << x << " " << i.index() << "\n";
                else std::cout << x << " end()\n";
            }
        
            steady_clock::time_point end = steady_clock::now();
            std::cout << "N=" << N << " took " << duration_cast<microseconds>(end - start).count() / (N+1) << " usec/lookup, "
                << refs/(N+1) << " refs/lookup "
                << incs/(N+1) << " incs/lookup\n";
        }
        return 0;
    }