template<typename T> struct tuple_size;
template<typename T> struct tuple_size<T const>: tuple_size<T> {};

template<class T, class = typename tuple_size<T>::type>
void f(int){}
template<class> void f(long){}

int main()
{
    f<void()>(0);
}