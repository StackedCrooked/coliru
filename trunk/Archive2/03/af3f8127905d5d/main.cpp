    #include <stdint.h>
     
    typedef uint16_t flag_t;
    enum : flag_t
    {
    MY_FLAG = 0x01,
    };
     
    static constexpr flag_t NOT1(flag_t f) { return f << ((sizeof(flag_t) / 2) * 8); }
     
    struct Foo
    {
    static constexpr flag_t NOT(flag_t f) { return f << ((sizeof(flag_t) / 2) * 8); }
    static constexpr flag_t FLAG_DEF = NOT(MY_FLAG);
    };
     
    int main(void)
    {
    }