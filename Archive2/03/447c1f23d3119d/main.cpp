
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

void call_undefined();

int main () {
    x xx;
    if (xx.clearly_not_compile_time_get_null()) { call_undefined(); }
}