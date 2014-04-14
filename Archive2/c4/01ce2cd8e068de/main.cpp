template <typename T, typename U>
struct A
{};

template<class T>
struct B
{};


template <typename T, typename U>
struct B<A<T, U> >
{
    B(const A<T, U>& a) {};
};

int main() {}
