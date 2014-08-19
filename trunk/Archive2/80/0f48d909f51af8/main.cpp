template<typename T> struct foo;

template<> struct foo<int> { using type = int; };
template<> struct foo<double> { using type = double; };

template<typename T>
void bar(typename foo<T>::type);

int main()
{
    bar(0);
}