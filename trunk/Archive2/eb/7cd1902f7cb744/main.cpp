template<char... digits>
struct conv2bin;

template<char high, char... digits>
struct conv2bin<high, digits...> {
    static_assert(high == '0' || high == '1', "no bin num!");
    static int const value = (high - '0') * (1 << sizeof...(digits)) + 
                             conv2bin<digits...>::value;
};

template<char high>
struct conv2bin<high> {
    static_assert(high == '0' || high == '1', "no bin num!");
    static int const value = (high - '0');
};

template<char... digits>
constexpr int operator "" _b() {
    return conv2bin<digits...>::value;
}

int main() {
    int const v = 110110110_b;
}