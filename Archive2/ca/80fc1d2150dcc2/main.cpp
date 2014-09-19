<iostream>

enum Enum { one, two, };

/* working Base, non-abstract */
template<typename T>
struct Base1
{ 
    template<typename P>
        void foo(P p)
        { std::cout << "with P\n"; }

    template<typename P, Enum E>
        void foo(P p, Enum e=E)
        { std::cout << "with P and E\n"; }

    void foo(T t) 
    { std::cout << "with T\n"; }
};

/* Broken? */
template<typename T>
struct Base2
{ 
    template<typename P>
        void foo(P p)
        { std::cout << "with P\n"; }

    template<typename P, Enum E>
        void foo(P p, Enum e=E)
        { std::cout << "with P and E\n"; }

    virtual void foo(T t) = 0; /// <------------- difference
};

/* Derived */
template<typename T>
struct Int : Base2<T>
{ 
    virtual void foo(T t)
    { std::cout << "Int with T\n"; }
};

int main(void)
{
    /* Not a problem, use Base1 directly */
    Base1<int> b;
    b.foo("hello");
    b.foo<std::string, Enum::one>("hello");
    b.foo(4);

    /* Not a problem, use the Int::foo*/
    Int<int> i;
    i.foo(5);

    /* Problem!!, use Base2::foo */
    i.foo("hello");
    i.foo<std::string, Enum::one>("hello");
}
