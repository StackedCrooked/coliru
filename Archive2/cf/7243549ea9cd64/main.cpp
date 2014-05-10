// All the overloads being scouted: T == lightuserdata_t

// Base template
template <typename T, typename... Args>
inline T get(types<Args...>, lua_State* L, int index = -1) {
    return T(L, index);
}

// Specializations
template <>
inline nil_t get( types<nil_t>, lua_State* L, int index ) {
	if ( lua_isnil( L, index ) == 0 )
		throw sol::sol_error( "not nil" );
	return nil_t{ };
}

template<>
inline bool get( types<bool>, lua_State* L, int index ) {
	return lua_toboolean( L, index ) != 0;
}

// THIS ONE SHOULD GET PICKED
template<>
inline lightuserdata_t get( types<lightuserdata_t>, lua_State* L, int index ) {
	return{ lua_touserdata( L, lua_upvalueindex( index ) ) };
}

template<>
inline userdata_t get( types<userdata_t>, lua_State* L, int index ) {
	return{ lua_touserdata( L, index ) };
}

template<>
inline std::string get( types<std::string>, lua_State* L, int index ) {
	std::string::size_type len;
	auto str = lua_tolstring( L, index, &len );
	return{ str, len };
}

template<>
inline const char* get( types<const char*>, lua_State* L, int index ) {
	return lua_tostring( L, index );
}

template<>
inline type get( types<type>, lua_State* L, int index ) {
	return static_cast<type>( lua_type( L, index ) );
}

// THIS ONE GETS PICKED UP INSTEAD: HAVE I DERPED?
template <typename T>
inline T& get( types<userdata<T>>, lua_State* L, int index = 1 ) {
	userdata_t udata = get<userdata_t>( L, index );
	T* obj = static_cast<T*>( udata.value );
	return *obj;
}

int main () {
    
}