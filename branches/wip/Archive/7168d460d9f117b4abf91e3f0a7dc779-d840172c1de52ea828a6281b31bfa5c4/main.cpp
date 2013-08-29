template<int... I>
void foo() {}

int main()
{
    foo<2, 4, 6, 8>();
}