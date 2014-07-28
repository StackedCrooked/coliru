#include <utility>
#include <type_traits>

template<typename T>
struct fun
{
    fun(T&&){}
    fun(const T&){}
};

template<typename T>
using remove_cv_and_ref_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template<typename T>
fun<remove_cv_and_ref_t<T>> create_fun(T&& val)
{
    return fun<remove_cv_and_ref_t<T>>(std::forward<T>(val));
}
/*
template<typename T>
fun<T> create_fun(const T& val)
{
    return fun<T>(val);
}
*/
int main()
{
    int i = 1;
    const int ci = 2;

    fun<int> d = create_fun(1);
    fun<int> e = create_fun(i);
    //error: no viable conversion from fun<int&> to fun<int>
    //why is create_fun(T&& val) a better match than create_fun(const T& val)?
    fun<int> f = create_fun(ci);

    return 0;
}