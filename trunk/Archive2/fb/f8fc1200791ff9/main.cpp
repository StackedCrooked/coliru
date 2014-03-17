template<class T> constexpr auto X = 42;

int main()
{
        static_assert(X<int> == 42, "");
}