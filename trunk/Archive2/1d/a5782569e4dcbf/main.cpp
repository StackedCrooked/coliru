template<class T>
struct outer
{
    using type = T;
    
    template<type V>
    struct inner
    {
        static type value;
    };
};

template<class T>
template< typename outer<T>::type V >
typename outer<T>::type
outer<T>::inner<V>::value = {};

int main()
{
    (void)outer<int>::inner<42>::value;
}