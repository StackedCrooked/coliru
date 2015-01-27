struct foo {
    auto bar() -> decltype( *this ) { return *this; }
};

int main()
{
    auto romans = foo {}.bar().bar().bar();
}