template<typename T>
auto test(T&& t, decltype( (t = { 0. }), 0 ) = 0);

template<typename...>
void test(...);

int main()
{
    using T = decltype( test(0) );
    // initializing void
    T val = 0;
    // incrementing void
    ++val;
}