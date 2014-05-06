int i{3};
const int j{3};
extern const int k{3};

template <typename T, T&>
void f() {}

int main()
{
    f<int, i>();        // OK
    f<int const, j>();  // not valid template argument: 'j' has not external linkage
    f<int const, k>();  // OK
}