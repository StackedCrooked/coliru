void f()
{
    const char c_x = 0x81; // ok
    constexpr const char ce_c_x = 0x81; // ok
    constexpr signed const char ce_s_c_x = 0x81; // ok
    const char c_x2 = c_x;
    constexpr const char ce_c_x2 = ce_c_x;
    constexpr signed const char ce_s_c_x2 = ce_s_c_x;
    const char c_x_arr[] = {0x81}; // error: constant expression evaluates to 129 which cannot be narrowed to type 'char' [-Wc++11-narrowing]
}

int main();