#include <utility>
#include <iostream>

template <typename value_type, typename tag_type>
struct TaggedValue {
    typedef value_type T;
    typedef tag_type TTag;
    
    template<typename ...Args>
    TaggedValue(Args && ...args) : element(std::forward<Args>(args)...) { }
    
    operator const T& () const { return element; }
    operator T& () { return element; }

	TaggedValue& operator= ( TaggedValue&& value ) {
		element = std::move( value.val );
	}

	TaggedValue& operator= ( const TaggedValue& value ) {
		element = value.val;
	}

	TaggedValue& operator= ( T&& value ) {
		element = std::move( value );
	}

	TaggedValue& operator= ( const T& value ) {
		element = value;
	}
    
    T element;
};

template <typename tag_to, typename tag_from, typename T>
TaggedValue<T, tag_to> tagged_cast ( const TaggedValue<T, tag_from>& castee ) {
    static_assert( false, "There is no tag conversion for these types" );
}

template <typename T, typename tag>
TaggedValue<T, tag> tagged_cast<tag, tag, T> ( const TaggedValue<T, tag>& castee ) {
    return castee;
}

struct radians_tag {};
struct degrees_tag {};

template <typename T>
TaggedValue<T, radians_tag> tagged_cast<radians_tag, degrees_tag, T> ( const TaggedValue<T, degrees_tag>& castee ) {
    return castee * 0.0174532925;
}

template <typename T>
TaggedValue<T, degrees_tag> tagged_cast<degrees_tag, radians_tag, T> ( const TaggedValue<T, radians_tag>& castee ) {
    return castee * 57.2957795;
}

int main ( int argc, char* argv[] ) {
 
     TaggedValue<double, radians_tag> radians = 3.14159;
     TaggedValue<double, degrees_tag> degrees = 180.0;
     double asdegrees = tagged_cast<degrees_tag>( radians );
     double asradians = tagged_cast<radians_tag>( radians );
     std::cout << asdegrees << std::endl;
}