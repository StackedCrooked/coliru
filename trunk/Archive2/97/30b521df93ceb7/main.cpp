struct WithNested1 {
    template<class T> struct Nested {
        void foo(){}
    };
};

struct WithNested2 {
    template<class T> struct Nested {
        void bar(){}
    };
};

template<typename... Ts>
struct Test : Ts::template Nested<Test<Ts...>>...
{

};

int main()
{
    Test<WithNested1, WithNested2> test;
    test.foo();
    test.bar();
}