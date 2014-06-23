#include <iostream>
#include <type_traits>

template
    <
        typename Array,
        typename Element = typename std::remove_all_extents<Array>::type,
        std::size_t Size = sizeof(Array) / sizeof(Element),
        typename FlattenedArray = Element (&)[Size]
    >
constexpr FlattenedArray Flatten(Array &a)
{
    return reinterpret_cast<FlattenedArray>(a);
}

template
    <
        typename Array,
        typename Element = typename std::remove_all_extents<Array>::type
    >
void FillArray(Array& a, Element v)
{
    for (Element& e : Flatten(a))
    {
        e = v;
    }
}

template <typename Type, typename Functor>
void ForEachElement(Type& e, Functor f)
{
    f(e);
}

template <typename Type, std::size_t N, typename Functor>
void ForEachElement(Type (&a)[N], Functor f)
{
    for (Type& e : a)
    {
        ForEachElement(e, f);
    }
}

template
    <
        typename Array,
        typename Element = typename std::remove_all_extents<Array>::type
    >
void CheckArray(Array& a, Element v)
{
    bool error = false;
    
    ForEachElement(a, [v, &error](const Element& e){ if (e != v) error = true; });
    if (!error)
    {
        std::cout << "Success!" << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
}

int main()
{
    int a[2][3][5];
    int d = 42;
    
    FillArray(a, d);
    CheckArray(a, d);
}