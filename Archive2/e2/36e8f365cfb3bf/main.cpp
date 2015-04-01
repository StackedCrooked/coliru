struct B { constexpr B& operator=(B const&) {return *this;} };

template <B&> struct foo {};

int main()
{
    B a, b;
    foo<a=b> f;
};