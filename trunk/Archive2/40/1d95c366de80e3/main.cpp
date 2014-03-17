    #include <iostream>

    using namespace std;

    // declarations
    template<typename T>
    struct Foo_temp;

    namespace A {
       struct Foo_type;
       using Foo = Foo_temp<Foo_type>;
    }

    namespace B {
       struct Foo_type;
       using Foo = Foo_temp<Foo_type>;
    }

    namespace C {
       struct Foo_type;
       using Foo = Foo_temp<Foo_type>;
    }

    // definitions
    template<>
    struct Foo_temp<A::Foo_type> { /*...*/ };

    template<>
    struct Foo_temp<B::Foo_type> { /*...*/ };

    template<>
    struct Foo_temp<C::Foo_type> { /*...*/ };

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
