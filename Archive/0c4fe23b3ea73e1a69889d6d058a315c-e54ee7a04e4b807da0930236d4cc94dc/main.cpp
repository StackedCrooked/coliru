    template<typename T>
    struct foo {
      T t;
    };

    template<typename FooType>
    struct bar;

    template<typename T>
    struct bar<foo<T>> {
      T t; //<- how to get T here (preferably without using typedef in foo)
    };

    #include <type_traits>

    int main()
    {
        bar<foo<int>> b;
        static_assert(std::is_same<decltype(b.t), int>::value, "!");
    }
