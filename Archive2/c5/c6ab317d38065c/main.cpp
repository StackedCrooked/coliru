struct Base
{
    typedef int T;
};

template <typename T>
struct Der: public Base
{
    T val;
};

int main()
{
    decltype(Der<float>::val) i{0.0f};
    (void)i;
}