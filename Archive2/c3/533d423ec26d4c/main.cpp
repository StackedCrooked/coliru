    // g++ -std=c++11 -O2 -pedantic -pthread main.cpp && ./a.out
    #include <iostream>
    #include <stddef.h>
    #include <algorithm>
    
    struct Pair {
        int _data[2]; // _data[0] and _data[1] are consecutive, and _data[0] is at offset 0 (&Pair == &_data[0])
        int first() { return _data[0]; }
        int second() { return _data[1]; }
        int & operator[] ( size_t x ) { return _data[x]; }
        friend inline bool operator< ( const Pair & lhs, const Pair & rhs ) {
            return lhs._data[0] < rhs._data[0];
        }
//        friend inline void swap( Pair a, Pair b ) {}
//        friend inline void swap( Pair & a, Pair & b ) {}
//        friend inline void swap( Pair && a, Pair && b ) {}
/*
        friend inline void swap( Pair & a, Pair & b ) {
            for( int i=0; i<2; ++i ) std::swap( a._data[i], b._data[i] );
        }
*/
    };
    struct Pairs {
        int* _data;
        size_t _size;
        Pairs( int data[], size_t size ) : _data(data), _size(size) {}
        Pair & operator[] ( size_t x ) const { return *reinterpret_cast< Pair * >( _data + 2 * x ); }
        class iterator
            : public std::iterator<std::random_access_iterator_tag, Pair>
        {
            int * _p;
            size_t _size;
            size_t _x;
        public:
//        friend inline void swap( iterator & a, iterator & b ) { }
//        friend inline void swap( iterator && a, iterator && b ) { }
/*
        int first( size_t x ) const { return _data[x][0]; }
        int second( size_t x ) const { return _data[x][1]; }
        Pair & operator[] ( size_t x ) { return _data[x]; }
*/
            iterator() : _p(NULL), _size(0), _x(0) {}
            iterator( int* data, size_t size ) : _p(data), _size(size), _x(0) {}
            friend inline bool operator== (const iterator& lhs, const iterator& rhs) { return lhs._p == rhs._p && lhs._x == rhs._x; }
            friend inline bool operator!= (const iterator& lhs, const iterator& rhs) { return lhs._p != rhs._p || lhs._x != rhs._x; }
            Pair& operator* () { return *reinterpret_cast< Pair * >( _p + 2 * _x ); }
    //   iterator & operator= ( const iterator & rhs ) { _p[_x][0] = rhs._p[rhs._x][0]; _p[_x][1] = rhs._p[rhs._x][1]; return *this; }
            int first() { return _p[2*_x]; }
            int second() { return _p[2*_x+1]; }
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
            friend inline bool operator< ( const iterator & lhs, const iterator & rhs ) {
                return lhs._p[2*lhs._x] < rhs._p[2*rhs._x+1];
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

    //template<class ForwardIt1, class ForwardIt2>
    static inline void iter_swap(Pairs::iterator a, Pairs::iterator b)
    {
    }

    int main() {
    	int N=5;
    	int data[10]= {1,2,7,8,13,14,10,11,4,5};
    	Pairs pairs( data, N );
    	
	    std::cout << "unsorted" << std::endl;
    	for(int i=0; i<N; ++i)
    		std::cout << i << ": (" << pairs[i].first() << ", " << pairs[i].second() << ")" << std::endl;
    	
	    std::sort(pairs.begin(), pairs.end());
 
	    std::cout << "sorted" << std::endl;
        for(int i=0; i<N; ++i)
    		std::cout << i << ": (" << pairs[i].first() << ", " << pairs[i].second() << ")" << std::endl;

    	return 0;
    }

