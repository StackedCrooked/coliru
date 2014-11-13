template<typename T>
using my = T( T a, T b );

template<typename T> my<T> mymin;
template<typename T> my<T> mymax;
template<typename T> my<T> myfoo;

template <typename T>
T mymax (T a, T b) {
    return (a > b ? a : b);
}

template <typename T>
T mymin (T a, T b) {
    return (a < b ? a : b);
}
template <typename T>
T myfoo (T a, T b) {
    return mymax(a,b)+mymin(a,b);
}

int main()
{
    myfoo( 42, 42 );
}
