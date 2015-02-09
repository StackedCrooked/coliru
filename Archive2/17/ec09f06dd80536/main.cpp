#include <iostream>


template< typename type >
class numeric_range
{
    
    public:
    
        class iterator
        {
            
            public:
            
                iterator( type begin, type increment )
                    : m_value( begin )
                    , m_increment( increment )
                {
                }
                
            public:
            
                auto operator*() const 
                  -> type
                {
                    return m_value;
                }
                
                auto operator++()
                  -> void 
                {
                    m_value += m_increment;
                }
                
                auto operator==( const iterator &other )
                  -> bool
                {
                    return m_value == other.m_value;
                }
                
                auto operator!=( const iterator &other )
                  -> bool
                {
                    return !operator==( other );
                }
            
            private:
            
                type m_value;
                type m_increment;
            
        };
    
    public:
    
        numeric_range( type begin, type end, type increment = 1 )
            : m_begin( begin )
            , m_end( end )
            , m_increment( increment )
        {
        }
        
    public:
    
        auto begin()
          -> iterator
        {
            return { m_begin, m_increment };
        }
        
        auto end() const 
          -> iterator
        {
            return { m_end, m_increment };
        }
    
    private:
    
        type m_begin;
        type m_end;
        type m_increment;
    
};


template< class type >
auto make_numeric_range( type start, type end, type increment = 1 )
  -> numeric_range< type >
{
    return { start, end, increment };
}

auto main( int, char ** ) 
  -> int 
{
    for ( auto i : make_numeric_range( 0, 18, 5 ) )
    {
        printf( "%d ", i );
    }
    
    printf( "\nasd" );
    
    return 0;
}