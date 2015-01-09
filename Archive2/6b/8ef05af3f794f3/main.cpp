template <typename Derived>
struct B
{
    typedef typename Derived::Type Type;
};

template <typename T>
struct D : B< D<T> >
{
    typedef T Type;
};

int main()
{
	D<float> d;
}