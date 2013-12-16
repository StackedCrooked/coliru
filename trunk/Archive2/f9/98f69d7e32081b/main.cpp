
struct x {
    static constexpr int get_null () {
        return 0;
    }
};

int main () {
    x a;
    // How smart is the compiler?
    static_assert( a.get_null() == 0, "Woo!" );
}