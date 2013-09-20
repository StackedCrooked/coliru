template <typename T1, typename T2>
auto Add(const T1& arg1, const T2& arg2) -> decltype (arg1 + arg2)
{
    return arg1 + arg2;
}

struct foo
{
    decltype(0ULL) count;
};

template <class A>
void eatWarnings(A)
{
}

int main(int, char**)
{
    auto res = Add(1, 2L); // long int
    auto res2 = Add(res, 3LL); // long long int
    
    eatWarnings(res2);
    return 0;
}
