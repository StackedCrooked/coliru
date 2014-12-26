// boost concept check
template<typename T>
void func(T obj)
{
    BOOST_CONCEPT_ASSERT((isBeautiful<T>))
}

// the same with type traits
template<typename T>
void func(T obj)
{
    static_assert(isBeautiful<T>::value);
}