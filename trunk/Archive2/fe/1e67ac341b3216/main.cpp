#ifdef USE_TEMPLATE
template<typename C>
#endif
struct MyClass;

template<class T0> auto woot(T0) {}

#ifdef USE_TEMPLATE
template<typename C>
#endif
struct MyClass {
        template<class T0> friend auto woot(T0) {}
};

int main()
{
#ifdef USE_TEMPLATE
    woot( MyClass<int>{} );
#else
    woot( MyClass{} );
#endif
}