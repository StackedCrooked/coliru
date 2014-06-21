#include <iostream>
#include <type_traits>

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
        typename Element = typename std::remove_all_extents<Array>::type,
        std::size_t Size = sizeof(Array) / sizeof(Element),
        typename ConvertedArray = Element (&)[Size]
    >
ConvertedArray flatten(Array &a)
{
    return reinterpret_cast<ConvertedArray>(a);
}

int main()
{
    int a[2][3][5];
    int d = 42;
    
    for (int& e : flatten(a))
    {
        e = d;
    }
    
    bool error = false;
    
    ForEachElement(a, [d, &error](int& e){ if (e != d) error = true; });
    if (!error)
    {
        std::cout << "Success!" << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
}