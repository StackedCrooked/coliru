    // http://stackoverflow.com/questions/23480041/is-the-member-field-order-of-a-class-stable
    #include <iostream>
    #include <algorithm>
    #include <stddef.h>

    struct Pair {
        int _data[2]; // _data[0] and _data[1] are consecutive,
                      // and _data[0] is at offset 0 (&Pair == &_data[0])
        int _unused[6]; // simulate the compiler inserted some padding here
        int first() { return _data[0]; }
        int second() { return _data[1]; }
        int & operator[] ( size_t x ) { return _data[x]; }
        friend inline bool operator< ( const Pair & lhs, const Pair & rhs ) {
            return lhs._data[0] < rhs._data[0];
        }
        // it is unlikely that the compiler will add any padding to a struct
        // Pair, so sizeof(Pair) == sizeof(_data)
        // however, the standard doesn't preclude it, so we define our own
        // copy constructor and assignment operator to ensure that nothing
        // extraneous is stored
        Pair( const Pair& other ) {
            _data[0] = other._data[0];
            _data[1] = other._data[1];
        }
        const Pair& operator=( const Pair& other ) {
            _data[0] = other._data[0];
            _data[1] = other._data[1];
            return *this;
        }
    };

    struct Pairs {
        int* _data;
        size_t _size;
        Pairs( int data[], size_t size ) : _data(data), _size(size) {}
        Pair & operator[] ( size_t x ) const {
            return *reinterpret_cast< Pair * >( _data + 2 * x );
        }
        class rai
            : public std::iterator<std::random_access_iterator_tag, Pair>
        {
            int * _p;
            size_t _size;
            size_t _x;
        public:
            rai() : _p(NULL), _size(0), _x(0) {}
            rai( int* data, size_t size )
                : _p(data), _size(size), _x(0) {}
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
                if (_x >= _size) { _x = _size = 0; _p = NULL; }
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
            friend inline ptrdiff_t operator- ( const rai & lhs, const rai & rhs ) {
                if (lhs._p == NULL) return rhs._p == NULL ? 0 : rhs._size - rhs._x;
                else return lhs._x - rhs._x;
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
           std::cout << i << ": (" << pairs[i].first() << ", "
                     << pairs[i].second() << ")" << std::endl;
    	
        std::sort(pairs.begin(), pairs.end());
 
        std::cout << "sorted" << std::endl;
        for(int i=0; i<N; ++i)
    		std::cout << i
                << ": (" << pairs[i][0]  // same as pairs[i].first()
                << ", "  << pairs[i][1]  // same as pairs[i].second()
                << ")" << std::endl;

    	return 0;
    }
