template <typename T>
struct identity {using type=T;};
template <typename T>
using identity_t = typename identity<T>::type;

template <typename T>
void Set(T* a, identity_t<T> b) {
    *a = b;
}

int main()
{
    long long l;
    Set(&l, 1);
}