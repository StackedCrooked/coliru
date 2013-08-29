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
struct tagged_caster {
	TaggedValue<T, tag_to> operator() ( const TaggedValue<T, tag_from>& castee ) {
		static_assert( false, "There is no conversion for these tagged types" );
	}
};

template <typename tag, typename T>
struct tagged_caster<tag, tag, T> {
	TaggedValue<T, tag> operator() ( const TaggedValue<T, tag>& castee ) {
		return castee;
	}
};

template <typename tag_to, typename tag_from, typename T>
TaggedValue<T, tag_to> tagged_cast ( const TaggedValue<T, tag_from>& castee ) {
    return tagged_caster<tag_to, tag_from, T>()( castee );
}

template <typename tag, typename T>
TaggedValue<T, tag> tagged_cast ( const TaggedValue<T, tag>& castee ) {
	return tagged_caster<tag, tag, T>()( castee );
}

/////////////////////
/* Specializations */
/////////////////////
struct radians_tag {};
struct degrees_tag {};

template <typename T>
struct tagged_caster<radians_tag, degrees_tag, T> {
	TaggedValue<T, radians_tag> operator() ( const TaggedValue<T, degrees_tag>& castee ) {
		return castee * 0.0174532925;
	}
};

template <typename T>
struct tagged_caster<degrees_tag, radians_tag, T> {
	TaggedValue<T, degrees_tag> operator() ( const TaggedValue<T, radians_tag>& castee ) {
		return castee * 57.2957795;
	}
};

int main ( int argc, char* argv[] ) {
 
     TaggedValue<double, radians_tag> radians = 3.14159;
     TaggedValue<double, degrees_tag> degrees = 180.0;
     double asdegrees = tagged_cast<degrees_tag>( radians );
     double asradians = tagged_cast( radians );
     std::cout << asdegrees << std::endl;
     std::cout << asradians << std::endl;
}