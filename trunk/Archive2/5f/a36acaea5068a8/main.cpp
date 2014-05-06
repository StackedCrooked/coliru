    // clang++ -std=c++11 -O2 -pedantic -pthread main.cpp && ./a.out
    #include <iostream>
    #include <stddef.h>
    #include <algorithm>
    
    typedef int Int2[2];
    
    struct Pair {
        Int2 _data;
        Pair( const Pair & other ) : _data{ other.first(), other.second() } {}
        Pair & operator= ( const Pair & rhs ) { _data[0] = rhs.first(); _data[1] = rhs.second(); }
        int first() const { return _data[0]; }
        int second() const { return _data[1]; }
        friend inline bool operator< ( const Pair & lhs, const Pair & rhs ) {
            return lhs.first() < rhs.first();
        }
    };
    struct Pairs {
        Pair* _data;
        size_t _size;
        Pairs( int data[], size_t size ) : _data(reinterpret_cast < Pair* > ( data )), _size(size) {}
        int & first( size_t x ) const { return _data[x]._data[0]; }
        int & second( size_t x ) const { return _data[x]._data[1]; }
        Pair & operator[] ( size_t x ) { return _data[x]; }
        class iterator
            : public std::iterator<std::random_access_iterator_tag, Int2>
        {
            Pair* _p;
            size_t _size;
            size_t _x;
        public:
            iterator() : _p(NULL), _size(0), _x(0) {}
            iterator( Pair* data, size_t size ) : _p(data), _size(size), _x(0) {}
            friend inline bool operator== (const iterator& lhs, const iterator& rhs) { return lhs._p == rhs._p && lhs._x == rhs._x; }
            friend inline bool operator!= (const iterator& lhs, const iterator& rhs) { return lhs._p != rhs._p || lhs._x != rhs._x; }
            Pair & operator* () { return _p[_x]; }
            iterator& operator+=( ptrdiff_t n ) {
                _x += n;
                if (_x >= _size) { _x = _size = 0; _p = NULL; }
                return *this;
            }
            iterator& operator-=( ptrdiff_t n ) {
                if (n > _x) _x = 0;
                else _x -= n;
                return *this;
            }
            friend inline iterator operator+ ( iterator lhs, const ptrdiff_t n ) {
                lhs._x += n;
                if (lhs._x >= lhs._size) { lhs._x = lhs._size = 0; lhs._p = NULL; }
                return lhs;
            }
            friend inline iterator operator- ( iterator lhs, const ptrdiff_t n ) {
                if (n > lhs._x) lhs._x = 0;
                else lhs._x -= n;
                return lhs;
            }
            iterator& operator++ () { return *this += 1; }
            iterator& operator-- () { return *this -= 1; }
            friend inline ptrdiff_t operator- ( const iterator & lhs, const iterator & rhs ) {
                if (lhs._p == NULL) return rhs._p == NULL ? 0 : rhs._size - rhs._x;
                else return lhs._x - rhs._x;
            }
        };
        inline iterator begin() { return iterator(_data,_size); }
        static inline const iterator end() { return iterator(); }
    };
    
    int main() {
    	int N=5;
    	int data[10]= {1,2,7,8,13,14,10,11,4,5};
    	Pairs pairs( data, N );
    	
	    std::cout << "unsorted" << std::endl;
    	for(int i=0; i<N; ++i)
    		std::cout << i << ": (" << pairs.first(i) << ", " << pairs.second(i) << ")" << std::endl;
    	
	    std::sort(pairs.begin(), pairs.end());
 
	    std::cout << "sorted" << std::endl;
	    for(int i=0; i<N; ++i)
		    std::cout << i << ": (" << pairs.first(i) << ", " << pairs.second(i) << ")" << std::endl;

    	return 0;
    }

