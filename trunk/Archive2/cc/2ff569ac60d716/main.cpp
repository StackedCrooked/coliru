#define is_number(S) \
               S[0]>='1' && S[0]<='9' && \
    (!S[1] || (S[1]>='0' && S[1]<='9' && \
    (!S[2] || (S[2]>='0' && S[2]<='9' && \
    (!S[3] || (S[3]>='0' && S[3]<='9' && \
    (!S[4] || (S[4]>='0' && S[4]<='9' && \
     !S[5]))))))))

int main()
{
    static_assert( is_number( "123" ), "123 failed" );
    static_assert( is_number( "0" ), "0 failed" );
    static_assert( is_number( "" ), "empty string failed" );
    static_assert( is_number( "1.23" ), "1.23 failed" );
    static_assert( is_number( "abc" ), "abc failed" );
}
