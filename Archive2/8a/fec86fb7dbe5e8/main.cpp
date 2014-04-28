#include <cassert>
#include <cstddef>

template <std::size_t n>
static int destruct( int* L ) {
	for ( std::size_t i = 0; i < n; ++i ) {
		//stack::pop<light_user_data>( L, i );
	}
	//void* userdata = lua_touserdata( L, 0 );
	//T* obj = static_cast<T*>( userdata );
	//std::allocator<T> alloc{ };
	//alloc.destroy( obj );
    return 0;
}

int main () {
    typedef int (*lua_CFunction)( int* );
    lua_CFunction fx = &destruct<0>;
}