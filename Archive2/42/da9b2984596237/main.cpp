    #ifndef CHUNKY_H
    #define CHUNKY_H
    #include <vector>
    #include <cstddef>
    #include <cstdint>
    
    template<class T> class Chunky {
        std::vector< std::vector<T> * > _chunk;
     public:
        Chunky() = default;
        Chunky( size_t guess ) { extend( guess ); }
        ~Chunky() { for ( auto & it : _chunk ) delete it; }
        void extend( size_t x ) { _chunk.push_back( new std::vector<T>( x ) ); }
        size_t size() const { size_t sz=0; for (auto & it : _chunk) sz += it.size(); return sz; }
        T & at( size_t x, size_t y ) { return _chunk[x]->at(y); }
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
        Chunky<Element> c( 10 );
        int i = 100;    
        auto cit = c.begin();
        for( ; cit != c.end(); ++cit ) cit->_value = i++;
        c.extend( 20 );
        cit = c.begin() + 10;
        for( ; cit != c.end(); ++cit ) cit->_value = i++;
        for( auto & it : c ) std::cout << it._value << std::endl;
        return 0;
    }
