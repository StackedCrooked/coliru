template <template<class> class Derived, class T>
struct base
{
};

template <class T>
struct derived : public base<derived, T>
{
    derived()
        : base<::derived, T>()
    { }
};

int main(int argc, char **argv) {
}