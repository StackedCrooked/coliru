    #ifndef CHUNKY_H
    #define CHUNKY_H
    #include <vector>
    #include <cstddef>
    #include <chrono>
 
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::steady_clock;
     
    template<class T> class Chunky {
        std::vector< std::vector<T> * > _chunk;
        size_t _size = 0;
     public:
        Chunky() = default;
        Chunky( size_t guess ) { extend( guess ); }
        ~Chunky() { for ( auto & it : _chunk ) delete it; }
        void extend( size_t x ) {
            _chunk.push_back( new std::vector<T>( x ) );
            _size += x;
        }
        size_t size() const { return _size; }
        T & operator[]( size_t z ) { return at( z ); }
        T & at( size_t z ) {
            size_t x = 0;
            while( z >= _chunk[x]->size() ) z -= _chunk[x++]->size();
            return _chunk[x]->at(z);
        }
        class iterator
        : public std::iterator<std::forward_iterator_tag, int>
        {
            Chunky<T> * _tp = nullptr;
            size_t _x = 0;
            size_t _y = 0;
        public:
            iterator() = default;
            iterator(Chunky<T> * tp) : _tp(tp) {}
            bool operator!= (const iterator& other) const {
                return _tp != other._tp || _x != other._x || _y != other._y;
            }
            T & operator* () const { return _tp->_chunk[_x]->at(_y); }
            T * operator->() const { return &_tp->_chunk[_x]->at(_y); }
            iterator& operator++ () {
                if (++_y >= _tp->_chunk[_x]->size()) {
                    _y = 0;
                    if (++_x >= _tp->_chunk.size()) {
                        _x = 0;
                        _tp = nullptr;
                    }
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
    
    #endif
    
    //    #include "chunky.h"
    #include <iostream>
    
    struct Element
    {
        int _value = 0;
        Element() = default;
        Element(const Element&) = delete;
        Element(Element&&) = delete;
        Element& operator=(Element const&) = delete;
    };
    
    int main( int argc, char *argv[] )
    {
        Chunky<Element> c( 5 ); // 5 default constructed Elements
        int i = 0;    
        
        // Chunky allows range based for loop
        for( auto & it : c ) it._value = 100 + i++;
        
        // Pointers to elements are valid for the lifetime of the container
        Element * element_ptr = & c[4]; // Take address of one of the elements
        std::cout << "The fifth element has a value of " << element_ptr->_value << std::endl;
        
        size_t previous_size = c.size();
        
        c.extend( 10 ); // 10 more default constructed Elements

        std::cout << "Dereferencing pointer to fifth element after extend, value is still " << element_ptr->_value << std::endl;

        for( size_t k=0; k < 10; ++k )
            c[previous_size + k]._value = 1100 + i++;
        
        // random access to initial elements and newly extended elements
        c[3]._value = -3;
        c[13]._value = -13;
        
        std::cout << "\nThe Elements contain values of: " << std::endl;

        // range based for loop
        for( auto & it : c ) std::cout << it._value << std::endl;

        steady_clock::time_point start = steady_clock::now();

        previous_size = c.size();
        size_t extend_size = 1e7;
        c.extend( extend_size ); // 10 million more default constructed Elements
        for( size_t k=0; k < extend_size; ++k )
            c[previous_size + k]._value = 10000 + i++;
        steady_clock::time_point end = steady_clock::now();

        std::cout << "\nExtending by " << extend_size << " and initializing the Elements took "
              << duration_cast<milliseconds>(end - start).count()
              << " msec.\n";

        return 0;
    }
