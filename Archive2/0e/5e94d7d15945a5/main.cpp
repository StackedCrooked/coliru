
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
    static_assert( a.clearly_not_compile_time_get_null() == 0, "Woo!" );
}