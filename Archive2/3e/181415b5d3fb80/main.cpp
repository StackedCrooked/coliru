extern "C" typedef void callback(void*);

// free function version
template <typename T>
callback f;

template <typename T>
void f(void*)
{
}

// static member function version
template <typename T>
struct X
{
    static callback f;
};

template <typename T>
void X<T>::f(void*)
{
}

int main()
{
    f<int>(nullptr);
    X<int>::f(nullptr);
    return 0;
}