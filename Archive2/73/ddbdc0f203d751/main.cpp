
    template <typename T>
	struct has_function_get_null {
		typedef char yes[ 1 ];
		typedef char no[ 2 ];

		template <typename C>
		static yes& test( typename C::get_null* );

		template <typename>
		static no& test( ... );

		static const bool value = sizeof( test<T>( 0 ) ) == sizeof( yes );
	};

struct x {
    static constexpr int get_null () {
        return 0;
    }
    
    constexpr int member_get_null () {
        return 0;
    }
    
    int clearly_not_compile_time_get_null () {
        return 0;
    }
};

int main () {
    x a;
    // How smart is the compiler?
    static_assert( a.get_null() == 0, "Woo!" );
    static_assert( a.member_get_null() == 0, "Woo!" );
    static_assert( has_function_get_null<x>::value == 0, "Woo!" );
}