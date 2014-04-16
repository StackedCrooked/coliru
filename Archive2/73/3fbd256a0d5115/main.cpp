    #include <vector>
    #include <cstddef>
    #include <stdexcept>
     
    template<class T> class chunk_allocator {
        std::vector< std::vector<T> * > _chunk;
        size_t _size   = 0;
        T*     _active = nullptr;
        size_t _begin  = 0;
        size_t _end    = 0;
     public:
        chunk_allocator() = default;
        chunk_allocator( size_t guess ) { create( guess ); }
        ~chunk_allocator() { for ( auto & it : _chunk ) delete it; }
        T* create( size_t x ) {
            _chunk.push_back( new std::vector<T>( x ) );
            _size += x;
            return _chunk.back()->data();
        }
        size_t size() const { return _size; }
        T & operator[]( size_t z ) { return at( z ); }
        T & at( size_t z ) {
            if ( z < _begin || z >= _end ) {
                size_t x = 0;
                for( _end = 0; z >= _end && x < _chunk.size(); ++x)
                {
                    _begin = _end;
                    _end += _chunk[x]->size();
                    _active = _chunk[x]->data();
                }
                if (z >= _end) throw std::out_of_range("chunk_allocator at "+std::to_string(z));
            }
            return _active[z - _begin];
        }
        class iterator
        : public std::iterator<std::forward_iterator_tag, int>
        {
            chunk_allocator<T> * _tp = nullptr;
            size_t _x = 0;
        public:
            iterator() = default;
            iterator(chunk_allocator<T> * tp) : _tp(tp) {}
            bool operator!= (const iterator& other) const {
                return _tp != other._tp || _x != other._x;
            }
            T & operator* () const { return _tp->at(_x); }
            T * operator->() const { return &_tp->at(_x); }
            iterator& operator++ () {
                if (++_x >= _tp->size()) {
                    _x = 0;
                    _tp = nullptr;
                }
                return *this;
            }
            iterator& operator+= ( size_t x ) { while(x--) *this++; return *this; }
            friend inline iterator& operator+ ( iterator & lhs, size_t x ) { while(x--) ++lhs; return lhs; }
            friend inline iterator operator+ ( iterator lhs, size_t x ) { while(x--) ++lhs; return lhs; }
        };
        inline iterator begin() { return iterator(this); }
        static inline const iterator end() { return iterator(); }
    
    };
    
    #include <iostream>
    #include <chrono>
 
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::steady_clock;
    
    struct foo
    {
      int X;
      static int C;
      foo() : X(C++) {}
      foo(foo const&) = delete;
      foo&operator=(foo const&) = delete;
      foo(foo &&) = delete;
      foo&operator=(foo &&) = delete;
    };    
    int foo::C=0;    
    int main()
    {
        chunk_allocator<foo> C(3);
        auto a = C.create(1);
        auto b = C.create(4);
        auto c = C.create(3);        
        std::cout<<" a="<<a<<" a->X = "<<a->X<<'\n'
                 <<" b="<<b<<" b->X = "<<b->X<<'\n'
                 <<" c="<<c<<" c->X = "<<c->X<<'\n';
      
        steady_clock::time_point start = steady_clock::now();
    
        size_t create_size = 1e5;
        size_t iterations  = 1e2;
    
        for( size_t x = 0; x < iterations; ++x ) {
            C.create( create_size );
        }
    
        steady_clock::time_point end = steady_clock::now();
    
        std::cout << "\nCreating " << iterations << " times by " << create_size << " and initializing the Elements took "
            << duration_cast<milliseconds>(end - start).count()
            << " msec.\n";
    }
