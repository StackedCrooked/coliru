#include <type_traits>
#include <utility>
#include <iostream>

template <typename T>
class Obj;

template <typename T>
Obj<T> make_obj(T t);

template <typename T>
struct ret_obj_helper {
    // Here goes the original definition of ret_obj
    template <typename RetVal>
    RetVal ret_obj(T t) {return RetVal(make_obj(t).t);}
};

// I guess RetVal, having to be explicitly specified, better goes first (?)
template <typename RetVal, typename T>
RetVal ret_obj(T&& t)
{
    // Overcomplicated for the sake of perfect forwarding
    return ret_obj_helper<typename std::remove_reference<T>::type>{}.
      template ret_obj<RetVal>(std::forward<T>(t));
}

template <typename T>
class Obj {
private:
    T t;
    Obj (T t) : t(t) { }
    Obj() = delete;

    friend Obj make_obj<T>(T t);

    // Make all specializations of the member function template 
    // of ret_obj_helper<T> a friend, regardless of the return type
    template <typename RetVal>
    friend RetVal ret_obj_helper<T>::ret_obj(T t);
};

template <typename T>
Obj<T> make_obj(T t) { 
    return Obj<T>(t);
}

int main()
{
    std::cout << ret_obj<float>( 4 );
}