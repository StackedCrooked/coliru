#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class Buffer {
public:
    Buffer(size_t size):buffer_(size,'\0')
    {}
    char& operator[](size_t offset) {
        return buffer_[offset];
    }
private:
    std::string buffer_;
};


template< class T > struct array_access
{
    typedef void type;
};


// That's how boost::shared_ptr::operator[] template looks like for T
/*    typename boost::detail::sp_array_access< T >::type operator[] ( std::ptrdiff_t i ) const
{
    BOOST_ASSERT( px != 0 );
    BOOST_ASSERT( i >= 0 && ( i < boost::detail::sp_extent< T >::value || boost::detail::sp_extent< T >::value == 0 ) );

    return px[ i ];
}*/

template<> struct array_access<Buffer> { typedef char& type; };
template <> array_access< Buffer >::type boost::shared_ptr<Buffer>::operator[] ( std::ptrdiff_t i ) const
{
    BOOST_ASSERT( px != 0 );
    return (*px)[ i ];
}

int main(int argc,char** argv)
{
    return 0;
}

