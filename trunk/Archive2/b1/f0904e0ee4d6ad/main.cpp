template <class T>
struct list
{
    bool moreThan(T x, T y);
    bool lessThan(T x, T y);
};

template <class T>
bool (list<T>::*foo)(T x, T y) = & list<T>::moreThan; //this works

auto x = foo< int >;
