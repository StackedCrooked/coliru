

// avoid include stl headers to minimize ASM output
template <class T> struct  RemoveReference        {typedef T type;};
template <class T> struct  RemoveReference<T&>  {typedef T type;};
template <class T>inline T& Forward(typename RemoveReference<T>::type& t) { return t; }
template <bool, class T = void> struct EnableIf {};
template <class T> struct EnableIf<true, T> {typedef T type;};



// Tag types
struct A {};
struct B {};


template<typename ...T>
void match(T... t);




enum { Limit = 4 };


// stop condition
template<typename ...Args>
auto dispatch(const char*, const char*, Args&& ...args) -> typename EnableIf<(sizeof...(args) >= Limit)>::type
{
    match(Forward<Args>(args)...);
}


// runtime to compile-time bridge
template<typename ...Args>
auto dispatch(const char* b, const char* e, Args&& ...args) -> typename EnableIf<(sizeof...(Args) < Limit)>::type
{
    if (b == e)
    {
        match(Forward<Args>(args)...);
        return;
    }

    char c = *b++;

    switch (c)
    {
        case 'A': dispatch(b, e, A{}, Forward<Args>(args)...); break;
        case 'B': dispatch(b, e, B{}, Forward<Args>(args)...); break;
        default:
        {

            dispatch(b, e, Forward<Args>(args)...); break;
        }
    }
}


int main()
{
    { const char* c = "ABCDEF"; dispatch(c, c + sizeof(c)); }
}
