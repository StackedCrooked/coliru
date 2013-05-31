    #include <iostream>

    namespace detail
    {
        template<typename T, int A, int B>
        struct helper;
    }

    template <typename a>
    class A
    {
    public:
        template<int b, int c>
        void f();
    private:
        template<typename, int, int> friend struct detail::helper;
    };

    namespace detail
    {
        template<typename T, int A, int B>
        struct helper
        {
            static void call(T* p) { std::cout << "f<A, B>()" << std::endl; }
        };

        template<typename T, int A>
        struct helper<T, A, A>
        {
            static void call(T* p) { std::cout << "f<A, A>()" << std::endl; }
        };
    }

    template<typename a>
    template<int b, int c>
    void A<a>::f()
    {
        detail::helper<A<a>, b, c>::call(this);
    }

    int main()
    {
        A<int> inst;
        inst.f<1,1>();
        inst.f<1,2>();
    }
