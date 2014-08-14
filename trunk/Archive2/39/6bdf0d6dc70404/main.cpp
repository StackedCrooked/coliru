#include <iostream>
#include <cstdint>

namespace type{
    enum object_type {
      POSITIVE_INTEGER	= 0x02,
      NEGATIVE_INTEGER	= 0x03,
    };
}

union union_type {
    uint64_t u64;
    int64_t i64;
};

struct object {
   type::object_type type;
   union_type via;
} ;

struct object_char_sign {
    static inline void make( object & o, char v )
    {
        v < 0 ? o.type = type::NEGATIVE_INTEGER, o.via.i64 = v
                : o.type = type::POSITIVE_INTEGER, o.via.u64 = v ;
    }
} ;
    
int main()
{
    object o1 ;
    char v = 20 ;
    
    object_char_sign::make( o1, v ) ;
    
    return 0;
}
