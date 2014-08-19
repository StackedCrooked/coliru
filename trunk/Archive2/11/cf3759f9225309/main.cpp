template<typename T> struct foo;

struct foo<int> { using type = int; };
struct foo<double> { using type = double; };

template<typename T>
void bar(typename foo<T>::type);

int main()
{
    bar(0);
}