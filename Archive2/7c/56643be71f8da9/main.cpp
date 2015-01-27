#include <type_traits>
#include <utility>
#include <iostream>

template <typename T>
class Obj;

template <typename T>
Obj<T> make_obj(T t);

template <typename T>
struct ret_obj_helper {
    template <typename RetVal>
    RetVal call(T t) {return RetVal(make_obj(t).t);}
};

// I guess RetVal, having to be explicitly specified, better goes first (?)
template <typename RetVal, typename T>
RetVal ret_obj(T&& t)
{
    return ret_obj_helper<typename std::remove_reference<T>::type>{}
        .template call<RetVal>(std::forward<T>(t));
}

template <typename T>
class Obj {
private:
    T t; // Removed the reference to make the sample valid (no UB)
    Obj (T t) : t(t) { }
    Obj() = delete;

    friend Obj make_obj<T>(T t);

    template <typename RetVal>
    friend RetVal ret_obj_helper<T>::call(T t);
};

template <typename T>
Obj<T> make_obj(T t) { 
    return Obj<T>(t);
}

int main()
{
    std::cout << ret_obj<float>( 4 );
}