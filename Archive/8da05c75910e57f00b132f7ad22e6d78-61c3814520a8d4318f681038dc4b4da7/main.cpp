#include <utility>

template <typename value_type, typename tag_type>
struct TaggedValue {
    typedef value_type T;
    typedef tag_type TTag;
    
    T val;
    
    TaggedValue ( const T& init ) : val( init ) {
        
    }
    
    TaggedValue ( T&& init ) : val( std::move( init ) ) {
        
    }
    
    TaggedValue ( const TaggedValue& init ) : val( init.val ) {
        
    }
    
    TaggedValue ( TaggedValue&& init ) : val( std::move( init.val ) ) {
        
    }
    
    operator T& () {
         return val;   
    }
    
    operator const T& () const {
         return val;   
    }
    
    TaggedValue& operator= ( TaggedValue&& value ) {
         val = std::move( value.val );
    }
    
    TaggedValue& operator= ( const TaggedValue& value ) {
         val = value.val;
    }
    
    TaggedValue& operator= ( T&& value ) {
         val = std::move( value );
    }
    
    TaggedValue& operator= ( const T& value ) {
         val = value;
    }
};

struct radian_tag {};
struct degrees_tag {};

int main ( int argc, char* argv[] ) {
 
     TaggedValue<double, radian_tag> radians = 3.14159;
     TaggedValue<double, degrees_tag> degrees = 180.0;
     
}