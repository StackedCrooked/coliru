struct foo {
    // static data members are declared, but not defined, in the class
    // a constexpr SDM *must* be initialized on first declaration, but
    // this doesn't count as a definition
    static constexpr auto size = 48;
    static constexpr int value[size] = { 1, 2, 3 };
};

// definition of a foo::value
// some parts of this definition are in the scope of foo,
// so e.g. foo::size is visible

constexpr int foo::value[size]; // already initialized, so don’t add anything

int main()
{
    return &foo::value == &foo::value;
}