constexpr bool is_number_cont( const char* str )
{
    return !*str || ( *str >= '0' && *str <= '9' && is_number_cont( str + 1 ) );
}

constexpr bool is_number( const char* str )
{
    return *str >= '1' && *str <= '9' && is_number_cont( str + 1 );
}

int main()
{
    static_assert( is_number( "123" ), "123 failed" );
    static_assert( is_number( "0" ), "0 failed" );
    static_assert( is_number( "" ), "empty string failed" );
    static_assert( is_number( "1.23" ), "1.23 failed" );
    static_assert( is_number( "abc" ), "abc failed" );
}
