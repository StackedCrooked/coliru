namespace n1
{
    namespace n2
    {
        void A(int);
    }
    using n2::A;
}

struct X { };

namespace n1
{
    namespace n2
    {
        void A(int = 42) {}
    }
    using n2::A;
}

int main()
{
    n1::A();
}
