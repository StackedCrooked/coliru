namespace n1
{
    namespace n2
    {
        template <typename T, typename S>
        struct A;
    }
    
    namespace fwd { using n2::A; }
}

// stuff on n1::fwd::A;

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
    n1::n2::A <int> a;
    n1::A <int> b;
}