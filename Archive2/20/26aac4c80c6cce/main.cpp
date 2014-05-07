    // http://stackoverflow.com/questions/23480041/is-the-member-field-order-of-a-class-stable
    #include <iostream>
    #include <algorithm>
    #include <stddef.h>

    struct Pair {
        int & first() const { return data(0); }
        int & second() const { return data(1); }
        int & operator[] ( size_t x ) const { return data(x); }
        int & data( size_t x ) const { int* p = const_cast<int*>( reinterpret_cast<const int*>( this ) ); return p[x]; }
        friend inline bool operator< ( const Pair & lhs, const Pair & rhs ) {
            return lhs[0] < rhs[0];
        }
        // it is unlikely that the compiler will add any padding to a struct
        // Pair, so sizeof(Pair) == sizeof(_data)
        // however, the standard doesn't preclude it, so we define our own
        // copy constructor and assignment operator to ensure that nothing
        // extraneous is stored
        Pair( const Pair& other ) {
            data(0) = other[0];
            data(1) = other[1];
        }
        const Pair& operator=( const Pair& other ) {
            data(0) = other[0];
            data(1) = other[1];
            return *this;
        }
    };

    class Pairs {
        int* _data;
        size_t _size;
    public:
        Pairs( int data[], size_t size ) : _data(data), _size(size) {}
        Pair & operator[] ( size_t x ) const {
            return *reinterpret_cast< Pair * >( _data + 2 * x );
        }
        class rai
            : public std::iterator<std::random_access_iterator_tag, Pair>
        {
            int * _p = nullptr;
            size_t _size = 0;
            size_t _x = 0;
        public:
            rai() = default;
            rai( int* data, size_t size ) : _p(data), _size(size) {}
            friend inline bool operator== (const rai& lhs, const rai& rhs) {
                return lhs._p == rhs._p && lhs._x == rhs._x;
            }
            friend inline bool operator!= (const rai& lhs, const rai& rhs) {
                return lhs._p != rhs._p || lhs._x != rhs._x;
            }
            Pair& operator* () const {
                return *reinterpret_cast< Pair * >( _p + 2 * _x );
            }
            rai& operator+=( ptrdiff_t n ) {
                _x += n;
                if (_x >= _size) { _x = _size = 0; _p = nullptr; }
                return *this;
            }
            rai& operator-=( ptrdiff_t n ) {
                if (n > _x) _x = 0;
                else _x -= n;
                return *this;
            }
            friend inline rai operator+ ( rai lhs, const ptrdiff_t n ) {
                return lhs += n;
            }
            friend inline rai operator- ( rai lhs, const ptrdiff_t n ) {
                return lhs -= n;
            }
            friend inline bool operator< ( const rai & lhs, const rai & rhs ) {
                return *lhs < *rhs;
            }
            rai& operator++ () { return *this += 1; }
            rai& operator-- () { return *this -= 1; }
            friend inline ptrdiff_t operator-(const rai& lhs, const rai& rhs) {
                return lhs._p == NULL
                    ? (rhs._p == NULL ? 0 : rhs._size - rhs._x)
                    : lhs._x - rhs._x;
            }
        };
        inline rai begin() { return rai(_data,_size); }
        static inline const rai end() { return rai(); }
    };

    int main() {
        int N=5;
        int data[10]= {1,2,7,8,13,14,10,11,4,5};
    	Pairs pairs( data, N );
    	
		std::cout << "unsorted" << std::endl;
    	for(int i=0; i<N; ++i)
    	    std::cout << i << ": (" << pairs[i].first() << ", " << pairs[i].second() << ")" << std::endl;
    	
        std::sort(pairs.begin(), pairs.end());
 
        std::cout << "sorted" << std::endl;
        int i = 0;
        for(auto & it : pairs)
    		std::cout << i++ << ": (" << it[0] << ", " << it[1] << ")" << std::endl;

    	return 0;
    }
