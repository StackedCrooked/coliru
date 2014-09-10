template <typename T, int N>
class StaticAssert
{
    static_assert(N != 0, "error message");
};

int main()
{
    StaticAssert<int, 10> ok;
    
    StaticAssert<int, 0> nok;
}
