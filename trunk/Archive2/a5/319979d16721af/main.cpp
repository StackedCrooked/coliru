    #ifndef CHUNKY_H
    #define CHUNKY_H
    #include <vector>
    #include <cstddef>
    #include <cstdint>
    
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
            iterator& operator+= ( int x ) { while(x--) *this++; return *this; }
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
        Chunky<Element> c( 5 );
        int i = 100;    
        auto cit = c.begin();
        for( ; cit != c.end(); ++cit ) cit->_value = i++;
        
        c.extend( 10 );
        cit = c.begin() + 5;
        i = 1000;
        
        for( ; cit != c.end(); ++cit ) cit->_value = i++;

        // random access
        c[3]._value = -3;
        c[13]._value = -13;
        
        // range based for loop
        for( auto & it : c ) std::cout << it._value << std::endl;

        return 0;
    }
