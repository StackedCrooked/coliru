template<int... I>
struct foo {
    static constexpr int value[] = { I... };
};

int main()
{
    return foo<2, 4, 6, 8>::value[3];
}