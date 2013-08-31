namespace n1
{
    namespace n2
    {
        template <typename T, typename S>
        struct A;
    }
    using n2::A;
}

struct X { };

namespace n1
{
    namespace n2
    {
        template <typename T, typename S = X>
        struct A { };
    }
    using n2::A;
}

int main()
{
    n1::A<int> a;
}
