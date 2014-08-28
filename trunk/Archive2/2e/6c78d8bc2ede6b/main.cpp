struct A {
    void a() const;
};

struct B : A {};

template<typename U, void (U::*)() const> struct SFINAE {};
template<typename U> void Test(SFINAE<U, &U::a>*) { }

int main(void)
{
    Test<B>(0);
    return 0;
}