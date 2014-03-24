#include <cstdint>

template < class T > class encDecode{
            public:
            static T decode ( uint8_t* , int&  ) ;
            static int encode ( T , uint8_t * );
    };
    
template < class T > T encDecode< T > :: decode ( uint8_t * , int &  ) {
  return T();

}

int main()
{
    uint8_t* a;
    int i;
    encDecode< uint16_t >::decode( a , i );
}