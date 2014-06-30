void f()
{
    const char c_x = 0x81;                               // ok
    constexpr const char ce_c_x = 0x81;                  // ok
    signed const char s_c_x = 0x81;                      // ok
    constexpr signed const char ce_s_c_x = 0x81;         // ok
    const char c_x2 = c_x;                               // ok
    constexpr const char ce_c_x2 = ce_c_x;               // ok
    signed const char s_c_x2 = s_c_x;                    // ok
    constexpr signed const char ce_s_c_x2 = ce_s_c_x;    // ok
    const char c_x_arr[] = {0x81};                       // error: constant expression evaluates to 129 which cannot be narrowed to type 'char' [-Wc++11-narrowing]
    constexpr const char ce_c_x_arr[] = {0x81};          // error: constant expression evaluates to 129 which cannot be narrowed to type 'char' [-Wc++11-narrowing]
    signed const char s_c_x_arr[] = {0x81};              // error: constant expression evaluates to 129 which cannot be narrowed to type 'char' [-Wc++11-narrowing]
    constexpr signed const char ce_s_c_x_arr[] = {0x81}; // error: constant expression evaluates to 129 which cannot be narrowed to type 'char' [-Wc++11-narrowing]
}

int main();
