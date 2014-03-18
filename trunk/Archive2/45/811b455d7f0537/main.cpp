    #include <iostream>

    using namespace std;

    // declarations
    template<typename T>
    struct Foo_temp;

    namespace A {
       struct tag;
       using Foo = Foo_temp<tag>;
    }

    namespace B {
       struct tag;
       using Foo = Foo_temp<tag>;
    }

    namespace C {
       struct tag;
       using Foo = Foo_temp<tag>;
    }

    // definitions
    template<>
    struct Foo_temp<A::tag> { /*...*/ };

    template<>
    struct Foo_temp<B::tag> { /*...*/ };

    template<>
    struct Foo_temp<C::tag> { /*...*/ };

    // testing
    template<typename T>
    struct is_Foo : public std::false_type {};

    template<typename T>
    struct is_Foo<Foo_temp<T>> : public std::true_type {};

    int main ()
    {
        cout << is_Foo<int>() << endl;
    	cout << is_Foo<A::Foo>() << endl;
    }
