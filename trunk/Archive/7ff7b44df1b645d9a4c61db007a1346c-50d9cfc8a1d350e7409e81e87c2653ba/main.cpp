#include <utility>
#include <memory>

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
		return *this;
	}

	TaggedValue& operator= ( const TaggedValue& value ) {
		element = value.val;
		return *this;
	}

	T element;
};

struct dont_delete_me_bro;

template <typename T>
using raw = TaggedValue<T, dont_delete_me_bro>;

int main ( int argc, char* argv[] ) {
    std::unique_ptr<int> ptr( new int(24) );
    
    // Never worry if you should be deleting things ever again!
    raw<int*> explicitrawpointer = ptr.get();
    
}