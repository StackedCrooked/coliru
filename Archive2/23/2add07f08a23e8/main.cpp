

template <class D>
struct base_traits;

struct derived;

template<>
struct base_traits<derived>
{
    typedef int value_t;
};


template <class D>
struct base
{
    typedef typename base_traits<D>::value_t value_t;
};

struct derived : base<derived>
{
    typedef base_traits<derived>::value_t value_t;
};


int main(void)
{
    derived d;
}